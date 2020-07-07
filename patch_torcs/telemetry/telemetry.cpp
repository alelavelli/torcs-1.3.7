/***************************************************************************

    file                 : telemetry.cpp
    created              : Sat Feb 26 16:48:43 CET 2000
    copyright            : (C) 2000 by Eric Espie
    email                : torcs@free.fr
    version              : $Id: telemetry.cpp,v 1.7.6.1 2012/02/09 14:00:31 berniw Exp $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <bits/stdc++.h>  //umbi

#include <tgf.h>
#include <telemetry.h>

#include "tlm.h"

typedef struct Channel
{
    struct Channel	*next;
    const char		*name;	/* channel name */
    tdble		*val;	/* monitored value */
    tdble		scale;
} tChannel;

typedef struct Tlm
{
    FILE	*file;	/* associated file */
    char	*cmdfile;
    int		state;
    tdble	ymin;
    tdble	ymax;
    tChannel	*chanList;
} tTlm;

static tTlm	TlmData;


/*
 * Function
 *	TlmInit
 *
 * Description
 *	Init telemetry internal structures.
 *
 * Parameters
 *	none
 *
 * Return
 *	none
 */
void
TlmInit(tdble ymin, tdble ymax)
{
    TlmData.file	= (FILE*)NULL;
    TlmData.state	= 0;
    TlmData.ymin	= ymin;
    TlmData.ymax	= ymax;
    TlmData.chanList	= (tChannel*)NULL;
}


/*
 * Function
 *	TlmNewChannel
 *
 * Description
 *	Create a new channel
 *
 * Parameters
 *
 * Return
 *	channel ID or -1 if error
 */
void
TlmNewChannel(const char *name, tdble *var, tdble min, tdble max)
{
    tChannel	*curChan;

    curChan = (tChannel *)calloc(sizeof(tChannel), 1);
    if (TlmData.chanList == NULL) {
	TlmData.chanList = curChan;
	curChan->next = curChan;
    } else {
	curChan->next = TlmData.chanList->next;
	TlmData.chanList->next = curChan;
	TlmData.chanList = curChan;
    }

    curChan->name = name;
    curChan->val = var;
    if ((min == 0) && (max == 0)) {
	curChan->scale = 1.0;
    } else {
	curChan->scale = TlmData.ymax / max;
    }
}

void
TlmStartMonitoring(const char *filename)
{
  printf("Start monitoring\n");
    const int BUFSIZE = 1024;
	char	buf[BUFSIZE];
    FILE	*fout;
    /*FILE	*fcmd;*/
    tChannel	*curChan;
    int		i;

    GfOut("Telemetry: start monitoring\n");

    // Write header
    snprintf(buf, BUFSIZE, filename);//snprintf(buf, BUFSIZE, "telemetry/%s", filename);
    fout = TlmData.file = fopen(buf, "a");//fout = TlmData.file = fopen(buf, "w");
    if (fout == NULL) {
	      return;
    }
    curChan = TlmData.chanList;
    fprintf(fout, "time");
    if (curChan != NULL) {
      do {
          curChan = curChan->next;
          fprintf(fout, ",%s", curChan->name);
      } while (curChan != TlmData.chanList);
      fprintf(fout, "\n");
    }
    // WRITE HEADER only if file doesn't already exist
    /*struct stat buffer;
    if(stat (filename, &buffer) != 0){
      snprintf(buf, BUFSIZE, filename);//snprintf(buf, BUFSIZE, "telemetry/%s", filename);
      fout = TlmData.file = fopen(buf, "w");//fout = TlmData.file = fopen(buf, "w");
      if (fout == NULL) {
  	      return;
      }
      printf("non esiste: metti header\n");
      curChan = TlmData.chanList;
      fprintf(fout, "time");
      if (curChan != NULL) {
      	do {
      	    curChan = curChan->next;
      	    fprintf(fout, ", %s", curChan->name);
      	} while (curChan != TlmData.chanList);
      	fprintf(fout, "\n");
      }
    }
    else{
      printf("esiste: no header\n");
      snprintf(buf, BUFSIZE, filename);//snprintf(buf, BUFSIZE, "telemetry/%s", filename);
      fout = TlmData.file = fopen(buf, "a");//fout = TlmData.file = fopen(buf, "w");
      if (fout == NULL) {
  	      return;
      }
    }*/
    TlmData.state = 1;
}

void
TlmUpdate(double time)
{
    FILE	*fout;
    tChannel	*curChan;

    if (TlmData.state == 0) {
	return;
    }
    fout = TlmData.file;
    fprintf(fout, "%f", time);

    curChan = TlmData.chanList;
    if (curChan != NULL) {
	do {
	    curChan = curChan->next;
	    fprintf(fout, ",%f", curChan->scale * (*curChan->val));
	} while (curChan != TlmData.chanList);
    }
    fprintf(fout, "\n");
}


void
TlmStopMonitoring(void)
{
  char file_name_date[100];
	const int BUFSIZE = 256;
    char	buf[BUFSIZE];

    if (TlmData.state == 1) {
	fclose(TlmData.file);
    }
    TlmData.file = (FILE*)NULL;
    TlmData.state = 0;
    GfOut("Telemetry: stop monitoring\n");

    /*snprintf(buf, BUFSIZE, "sh %s", TlmData.cmdfile);
    system(buf);*/
    free(TlmData.cmdfile);
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    snprintf(file_name_date, 100, "cp telemetry/forza_ow%d_%d_%d.csv ~/raw_torcs_data/", (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday);
    //std::string str = "cp telemetry/forza_ow1.csv ~/baRricheLlo/raw_torcs_data/";
   //const char *command = str.c_str();
   system(file_name_date);
}

/*
 * Function
 *	TlmShutdown
 *
 * Description
 *	release all the channels
 *
 * Parameters
 *	none
 *
 * Return
 *	none
 */
void
TlmShutdown(void)
{
    if (TlmData.state == 1) {
	TlmStopMonitoring();
    }
    /* GfRlstFree((tRingList **)&TlmData.chanList); */
}
