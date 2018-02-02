/*
DHT 22 humidity and temperature sensor library

    Copyright (C) 2013  Fabio Angeletti - fabio.angeletti89@gmail.com

    See attached license.txt file

*/

/* Define to prevent recursive inclusion -----------------------------------*/
#ifndef __DHT22_H
#define __DHT22_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ----------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stdbool.h"
#include "init.h"

/* defines -----------------------------------------------------------------*/
/* Initially defined here. Now replaced to init.h*/
/* variables ---------------------------------------------------------------*/
static uint8_t DHT22data[6];
static float temperature1, humidity1;
 static float temperature2, humidity2;
#define NUMBER_OF_SESNORS 1
/* functions prototypes ----------------------------------------------------*/
void DHT22pinIn(uint16_t DHT22_DATA_PIN);
void DHT22pinOut(uint16_t DHT22_DATA_PIN);
void DHT22_Init(uint16_t DHT22_DATA_PIN);
bool DHT22_Read(uint16_t DHT22_DATA_PIN);
float DHT22getTemperature(void);
float DHT22getHumidity(void);
float convertCtoF(float cTemperature);

#ifdef __cplusplus
}
#endif

#endif
