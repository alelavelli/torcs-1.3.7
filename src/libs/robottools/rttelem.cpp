/***************************************************************************

    file                 : rttelem.cpp
    created              : Mon Feb 28 22:38:31 CET 2000
    copyright            : (C) 2000 by Eric Espie
    email                : torcs@free.fr
    version              : $Id: rttelem.cpp,v 1.8.2.3 2014/05/16 15:45:11 berniw Exp $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#if 0

/** @file
    		This is a collection of useful functions for using telemetry in a robot.
		You can see an example of telemetry usage in the human driver.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id: rttelem.cpp,v 1.8.2.3 2014/05/16 15:45:11 berniw Exp $
    @ingroup	robottools
*/

/** @defgroup telemetry		Telemetry tools for robots.
    The telemetry is only working with Linux.
    <br>The graphs are build by gnuplot.
    @ingroup	robottools
*/

#endif

#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <telemetry.h>
#include <robottools.h>
#include <tgf.h>
#include <portability.h>

static tTelemItf	tlm;
static tModList		*modlist = (tModList*)NULL;
#if 0
#endif

/** Initialization of a telemetry session.
    @ingroup	telemetry
    @param	ymin	Minimum value for Y.
    @param	ymax	Maximum value for Y.
    @return	None
 */
void RtTelemInit(tdble ymin, tdble ymax)
{
	const int BUFSIZE = 256;
	char	buf[BUFSIZE];
	tModInfo	*curModInfo;

	memset(&tlm, 0, sizeof(tTelemItf));
	/*snprintf(buf, BUFSIZE, "%smodules/telemetry/%s.%s", "telemetry", GetLibDir (), DLLEXT);*/
	snprintf(buf, BUFSIZE, "%smodules/telemetry/%s.%s",  GetLibDir (), "telemetry", DLLEXT);
	if (GfModLoad(TLM_IDENT, buf, &modlist)) return;
	GfOut("--- %s loaded ---\n", modlist->modInfo->name);
	curModInfo = modlist->modInfo;
	curModInfo->fctInit(curModInfo->index, &tlm);

	tlm.init(ymin, ymax);
#ifdef later
#endif
}


/** Create a new telemetry channel.
    @ingroup	telemetry
    @param	name	Name of the channel.
    @param	var	Address of the variable to monitor.
    @param	min	Minimum value of this variable.
    @param	max	Maximum value of this variable.
    @return	None
 */
void RtTelemNewChannel(const char * name, tdble * var, tdble min, tdble max)
{
	tlm.newChannel(name, var, min, max);
#if 0
#endif
}

/** Start recording into a file.
    @ingroup	telemetry
    @param	filename	name of the file to use.
    @return	none.
 */
void RtTelemStartMonitoring(const char * filename)
{
	tlm.startMonitoring(filename);
#if 0
#endif
}

/** Stop recording and close the file.
    @ingroup	telemetry
    @return	none
 */
void RtTelemStopMonitoring(void)
{
	tlm.stopMonitoring();
#if 0
#endif
}

/** Record a new set of values.
    @ingroup	telemetry
    @param	time	current time.
    @return	None.
 */
void RtTelemUpdate(double time)
{
	tlm.update(time);
#if 0
#endif
}

/** Deinstall the telemetry module.
    @ingroup	telemetry
    @return	none.
 */
void RtTelemShutdown(void)
{
	tlm.shutdown();
	GfModUnloadList(&modlist);
#if 0
#endif
}
