/***************************************************************************

    file        : human.h
    created     : Sat May 10 19:12:46 CEST 2003
    copyright   : (C) 2003 by Eric Espi�                        
    email       : eric.espie@torcs.org   
    version     : $Id: human.h,v 1.3.2.3 2013/08/29 20:03:44 berniw Exp $                                  

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
 
/** @file    
    		
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id: human.h,v 1.3.2.3 2013/08/29 20:03:44 berniw Exp $
*/

#ifndef _HUMAN_H_
#define _HUMAN_H_

typedef struct HumanContext
{
	int		NbPitStops;
	int		LastPitStopLap;
	int 	AutoReverseEngaged;
	tdble	Gear;
	tdble	distToStart;
	tdble	clutchtime;
	tdble	clutchdelay;
	tdble	ABS;
	tdble	AntiSlip;
	int		lap;
	tdble	prevLeftSteer;
	tdble	prevRightSteer;
	tdble	paccel;
	tdble	pbrake;
	int		manual;
	int		Transmission;
	int		NbPitStopProg;
	int		ParamAsr;
	int		ParamAbs;
	int		RelButNeutral;
	int		SeqShftAllowNeutral;
	int		AutoReverse;
	int		drivetrain;
	int		autoClutch;
	tControlCmd	*CmdControl;
	int		MouseControlUsed;
	int		lightCmd;
    //AL
    tdble lap_n;
    tdble angle;
    tdble track_angle;
    tdble track_pos;
    tdble track_sensors_0;
    tdble track_sensors_1;
    tdble track_sensors_2;
    tdble track_sensors_3;
    tdble track_sensors_4;
    tdble track_sensors_5;
    tdble track_sensors_6;
    tdble track_sensors_7;
    tdble track_sensors_8;
    tdble track_sensors_9;
    tdble track_sensors_10;
    tdble track_sensors_11;
    tdble track_sensors_12;
    tdble track_sensors_13;
    tdble track_sensors_14;
    tdble track_sensors_15;
    tdble track_sensors_16;
    tdble track_sensors_17;
    tdble track_sensors_18;
    //END AL
} tHumanContext;


extern tHumanContext *HCtx[];

extern int joyPresent;

#endif /* _HUMAN_H_ */ 



