/** -------------------------------------------------------------------------- 
 * File: main.cpp
 * Created Date: 11-28-2020
 * Author: Thomas Ose
 * ---------------------------------------------------------------------------
 * Last Modified: Saturday, 28th November 2020 10:00:35 pm
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
 * 11-28-2020	tmo Initial code 	
 * --------------------------------------------------------------------------- */
#include "OMSSmallLightingController.h"

/**
 * @brief  CallBack function for the sensor check
 * @note   Read the photo cell and sees if the light is required.  Sets NEED_LIGHT appropriately.
 *          If the value changes then also resets the relay counters.
 * @retval None
 */
void CheckSensor_Callback()
{
    int value = digitalRead(LIGHT_SENSOR);
    delay(10);
    if (LastSensorRead != value)
    {
        LastSensorRead = value;
        LightRequire = value;
        if (LightRequire != LastLightStatus)
        {
            if (LightRequire && !LastLightRequire)
            {
                LastLightRequire = true;
            }
            if (!LightRequire && LastLightRequire)
            {
                LastLightRequire = false;
            }
        }
        LastLightStatus = LightRequire;
    }
}

/**
 * @brief  Control all the LED outputs
 * @note   LightRequired controll the action of the LED.  
 *              LED_INSIDE is always on
 *              All Other LED turn on with LightRequired 
 * @retval None
 */
void CheckLED_CallBack()
{
    if (LightRequire)
    {
        digitalWrite(LED_SIDE, ON);
        digitalWrite(LED_FRONT, ON);
        digitalWrite(LED_BACK, ON);
    }
    if (!LightRequire)
    {
        digitalWrite(LED_INSIDE, ON);
        digitalWrite(LED_SIDE, OFF);
        digitalWrite(LED_FRONT, OFF);
        digitalWrite(LED_BACK, OFF);
    }
}

/**
 * @brief  Setup of default functions and values for the application
 * @note   
 * @retval None
 */
void setup()
{
    LastLightRequire = false;
    LightRequire = false;
    LastSensorRead = 0;

    pinMode(LED_BACK, OUTPUT);
    pinMode(LED_INSIDE, OUTPUT);
    pinMode(LED_SIDE, OUTPUT);
    pinMode(LED_FRONT, OUTPUT);

    pinMode(LIGHT_SENSOR, INPUT);
 
    runner.init();

    runner.addTask(CheckSensor);
    CheckSensor.enable();
 
    runner.addTask(CheckLED);
    CheckLED.enable();
 
 
    digitalWrite(LED_BACK, OFF);
    digitalWrite(LED_INSIDE, ON);
    digitalWrite(LED_SIDE, OFF);
    digitalWrite(LED_FRONT, OFF);
}

/**
 * @brief  Main program loop
 * @note   
 * @retval None
 */
void loop()
{
    runner.execute();
}
