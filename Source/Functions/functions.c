/**
*	@file functions.c
*	@brief This file contains all functions used for user and memory management.
*	
*/

#include "FreeRTOS.h"
#include "task.h"
#include "functions.h"
#include "string.h"
//extern char data[DATA_STR_LEN+1];
//extern char packageTemp[DATA_STR_LEN+1];


void sendToUart(char *first)
{
	while(*(first)!=0)
	{
		while(!USART_FLAG_TXE);
		USART_SendData(USARTID, *(first));
		while(!USART_GetFlagStatus(USARTID, USART_FLAG_TC));
		first++;
	}
}

//void sendToUart1(char *first)
//{
//	while(*(first)!=0)
//	{
//		while(!USART_FLAG_TXE);
//		USART_SendData(USARTID1, *(first));
//		while(!USART_GetFlagStatus(USARTID1, USART_FLAG_TC));
//		first++;
//	}
//}

void cleanBuffer (char *first, int size)
{   first=0;
	while(size!=0)
	{
		*(first)=0x00;
		size--;
		first++;
	}

}
bool compareID(uint8_t *id1, uint8_t *id2)
{
	if(*id1 == *id2 &&
			*(id1+1) == *(id2+1) &&
			*(id1+2) == *(id2+2) &&
			*(id1+3) == *(id2+3) &&
			*(id1+4) == *(id2+4))
			return true;
	return false;
}

bool isUserValid(User *userList,uint8_t numUser, uint8_t* ID)
{
	uint8_t i;
	for (i=0; i<numUser; i++)
	{
		if(compareID((userList+i)->ID,ID))
			return true;
	}
	return false;
}

uint8_t initSuperUser(User *userArray)
{
		
		uint8_t numberOfUsers = 4;
		
		userArray[0].ID[0] = 250; //FA
		userArray[0].ID[1] = 18;  //12
		userArray[0].ID[2] = 68; //44
		userArray[0].ID[3] = 224; //EO
		userArray[0].ID[4] = 76; // 4C
		strcpy(userArray[0].firstName,"Marko"); 
		strcpy(userArray[0].lastName,"Svec");
	
		userArray[1].ID[0] = 202; //CA
		userArray[1].ID[1] = 210; //D2
		userArray[1].ID[2] = 104; //68
		userArray[1].ID[3] = 224; //EO
		userArray[1].ID[4] = 144; //90
		strcpy(userArray[1].firstName,"Adam"); 
		strcpy(userArray[1].lastName,"Sedmak");
	
		userArray[2].ID[0] = 197; //C5
		userArray[2].ID[1] = 31; //1F
		userArray[2].ID[2] = 252; //FC
		userArray[2].ID[3] = 2; // 2
		userArray[2].ID[4] = 36; // 24
		strcpy(userArray[2].firstName,"Josko"); 
		strcpy(userArray[2].lastName,"Rogulj");
		
		
		userArray[3].ID[0] = 170; //AA
		userArray[3].ID[1] = 14; //0E
		userArray[3].ID[2] = 101; //65
		userArray[3].ID[3] = 224; //E0
		userArray[3].ID[4] = 33; //21
		strcpy(userArray[3].firstName,"Matea"); 
		strcpy(userArray[3].lastName,"Mihalj");
		
		return numberOfUsers;	
}

void writeSuperUser(User *superUser)
{
		uint32_t startAddress = 0x08008000;	//Randomly selected address. It can be any other as well. 
		uint32_t currAddress = startAddress + 1;
		uint8_t numberOfUsers = 4;
	
		if(*(__IO uint8_t*)(startAddress) == 0xA5)
			return;
	
		FLASH_Unlock();
		FLASH_EraseSector(FLASH_Sector_2, VoltageRange_3);
		FLASH_ProgramByte(startAddress,0xA5);
	
		for(uint8_t i=0; i<numberOfUsers; i++)
		{
			for(int j=0; j<5; j++)
			{
				FLASH_ProgramByte(currAddress,superUser[i].ID[j]);
				currAddress++;
			}
			for(int j=0; j<sizeof((superUser+i)->firstName); j++)
			{
				FLASH_ProgramByte(currAddress,superUser[i].firstName[j]);
				currAddress++;
			}
			for(int j=0; j<sizeof((superUser+i)->lastName); j++)
			{
				FLASH_ProgramByte(currAddress,superUser[i].lastName[j]);
				currAddress++;
			}
		}
		FLASH_Lock();	
}

void sendDHT22(float temperature, float humidity, uint8_t subID)
{
		char data[DATA_STR_LEN+1];
		char *message;
		uint8_t ctrl = 0x3A;				//Defines type of a message. For instance, this means data message.
		sprintf(data, "%.3f,%.3f", temperature, humidity); //Add temperature and humidity divided by comma.
		message = createPackage(DHT_ID, subID, ctrl, data);
	  GPIO_SetBits(LEDPORT, LED4PIN);
//	
		sendToUart(message);	

	  GPIO_ResetBits(LEDPORT, LED4PIN);


		cleanBuffer (message, stringLength(message));
		cleanBuffer (data, stringLength(message));
}

void sendDistance(float distance, float position)
{
		//Implement send function
}

void sendInitialMap(float *mapArray, int number)
{
		//Implement send function
}


void writeInitialMap(float *initial_map)
{
		uint32_t startAddress = 0x08010000;	//Randomly selected address. It can be any other as well. 
		uint32_t currAddress = startAddress + 1;
//		uint8_t numberOfUsers = 30;
	
		if(*(__IO uint8_t*)(startAddress) == 0xA7)
			return;
	
		FLASH_Unlock();
		FLASH_EraseSector(FLASH_Sector_2, VoltageRange_3);
		FLASH_ProgramByte(startAddress,0xA7);
	
		for(uint8_t i=0; i<30; i++)
		{

		
				FLASH_ProgramByte(currAddress,initial_map[i]);
				currAddress++;

		}
		FLASH_Lock();	
}