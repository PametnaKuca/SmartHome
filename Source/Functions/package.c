#include "package.h"
#include "functions.h"
short stringLength(char *str)
{
	char *tempStr = str;
	short len = 0;
	while(*(tempStr++) != '\0')
		len++;
	return len;
}

char* stringXOR(char *message)
{
		char xorString[2];
		char *tempMsg = message + 1;
		xorString[0] = *message;
		while(*tempMsg!='\0')
			xorString[0] = xorString[0] ^ *(tempMsg++);
		xorString[1] = '\0';
		return xorString;		
}

char* createPackage(uint8_t ID, uint8_t subID, uint8_t ctrl, char *data)
{
			
	char packageTemp[MAX_PACK_LEN + 1];
char *xorStr;
	short size = stringLength(data) + 4; // Message length + ID byte + SUB_ID byte + CTRL byte + XOR byte
	char protocolData[] ={(char)ID , (char)subID, (char)ctrl, '\0'}; //zadnji bajt mora biti \0 zbog sprintf-fje
//cleanBuffer (packageTemp, stringLength(packageTemp));
//cleanBuffer (&protocolData[0], stringLength(protocolData));	
	sprintf(packageTemp, "%.3d", size); //
	
//		memcpy(&packageTemp[3],protocolData,4);
//	memcpy(&packageTemp[7],data,stringLength(data)); 
//	xorStr = stringXOR(packageTemp);
//	memcpy(&packageTemp[size+3], xorStr,1);;
	strcat(packageTemp,protocolData);
	strcat(packageTemp,data); 
	xorStr = stringXOR(packageTemp);
	strcat(packageTemp, xorStr);
	return packageTemp;
}
