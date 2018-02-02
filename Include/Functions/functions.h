/**
*	@file functions.h
*	@brief This file contains all function declartions used for user and memory management.
*	
*/

#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_flash.h"
#include "init.h"
#include "package.h"

#define NAME_LEN 15
#define DATA_STR_LEN 20		//length of the string which is sent to uart
#define INIT_MAP_STR_LEN 	DATA_STR_LEN*((int)(ANGLEmax/ANGLE)+1)	//lengt of the string sent to uart which contains initial map


typedef struct UserStruct {
	uint8_t ID[5];
	char firstName[NAME_LEN+1];
	char lastName[NAME_LEN+1];
} User;


/**
*	This function is used to send a string of chars to the serial port.
*	@param	first	Pointer to the first element of the input char array.
*/
void cleanBuffer (char *first, int size);
void sendToUart(char *first);
void sendToUart1(char *first);
/**
*	This function compares the input card ID with every users' card ID to see if the card belongs to a valid user.
*	@param	User list and ID	Pointer to the first element of the input array.
*/
bool isUserValid(User *userList,uint8_t numUser, uint8_t* ID);
/**
* Function compares two ID arrays.
* @param id1 and id2 arrays.
*/
bool compareID(uint8_t *id1, uint8_t *id2);
/**
*	Functions returns array of super users throught the userArray pointer
*	@param userArray pointer
*/
uint8_t initSuperUser(User *userArray);
/**
*	Functions writes hardcoded super users to flash.
*	@param superUser array.
*/
void writeSuperUser(User *superUser);
/**
*	The function packs temperature and humidtiy into requested data form
* and sends it over serial port.
* @param temperature, humidity and subID
*/
void sendDHT22(float temperature, float humidity, uint8_t subID);
/**
*	The functions packs distance and position into requested data form
* and sends it over serial port.
*	@param distance and position
*/
void sendDistance(float distance, float position);
/**
* The function sends initial space map over serial port.
* @param map array, number of array elements
*/
void sendInitialMap(float *mapArray, int number);

/*	Functions writes initial map to flash.
*	@param superUser array.
*/
void writeInitialMap(float *initial_map);
