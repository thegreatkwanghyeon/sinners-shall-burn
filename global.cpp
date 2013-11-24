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

float soundVolume = 50;
float musicVolume = 50;

int killEnemyNum=0;
int getCouponNum=0;
int useRebuildNum=0;
int useHintNum=0;

bool cheatButton=false;
bool cheatMap=false;

void resetChallenge(){
	killEnemyNum=0;
	getCouponNum=0;
	useRebuildNum=0;
	useHintNum=0;
}