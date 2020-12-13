/** -------------------------------------------------------------------------- 
 * File: OMSSmallLightingController.h
 * Created Date: 11-28-2020
 * Author: Thomas Ose
 * ---------------------------------------------------------------------------
 * Last Modified: Saturday, 28th November 2020 10:04:18 pm
 * Modified By: Thomas Ose (tmo@osemicro.com>)
 * ---------------------------------------------------------------------------
 * Copyright (c) 2016 - 2020 OMS(re)Models
 * 
 *  This source file is subject of the GNU general public license 2,
 *  that is available at the world-wide-web at
 *  http://www.gnu.org/licenses/gpl.txt
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  copy of this software and associated documentation files.  The above
 *  copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 * ---------------------------------------------------------------------------
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	----------------------------------------------------------
 * 11-28-2020	tmo Created initial code base	
 * --------------------------------------------------------------------------- */

#ifndef _OMSSMALLLIGHTINGCONTROLLER_h
#define _OMSSMALLLIGHTINGCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "TaskScheduler.h"

// Define variables

#define LED_BACK 2
#define LED_INSIDE 3
#define LED_SIDE 4
#define LED_FRONT 1

#define LIGHT_SENSOR 0

#define SECONDS 1000  // 1000 miliseconds
#define MINUTES 60000 // 60 Seconds

#define ON LOW
#define OFF HIGH

int LastSensorRead = 0;
bool LightRequire = true;
bool LastLightRequire = true;
bool LastLightStatus = true;

// task scheduler variables
Scheduler runner; // the main runner task

void CheckSensor_Callback();
void CheckLED_CallBack();

Task CheckSensor(1000, TASK_FOREVER, &CheckSensor_Callback);
Task CheckLED(2000, TASK_FOREVER, &CheckLED_CallBack);

#endif