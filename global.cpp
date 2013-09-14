#include "global.h"

std::wstring MTW( const char* string){
	int stringSize = MultiByteToWideChar(CP_UTF8, 0, string, strlen(string), NULL, 0);
	std::vector<wchar_t> tmpString;
	std::wstring returnString;

	tmpString.resize(stringSize);
	MultiByteToWideChar(CP_UTF8, 0, string,strlen(string), &tmpString[0], stringSize);

	for(unsigned int i=0;i<tmpString.size();i++){
		returnString.push_back(tmpString[i]);
	}

	return returnString;
}

int soundVolume = 100;
int musicVolume = 100;