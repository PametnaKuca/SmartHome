/**
*	@file package.h
*	@brief This file contains all function declartions used for creating protocol package.
*	
*/

#include<string.h>
#include<stdio.h>
#include "init.h"

#define MAX_PACK_LEN 999

/**
*	The function measures and returns string length.
* @param string which we want to measure
*/
short stringLength(char *str);
/**
*	The function packs all the data into data package and returns this package
* as a string. It adds XOR byte at the end for error detection.
* @param sensor type ID, sensor sub ID, control byte, data string to send
*/
char* createPackage(uint8_t ID, uint8_t subID, uint8_t ctrl, char *data);
