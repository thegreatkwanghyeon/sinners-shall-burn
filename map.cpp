#include "map.h"

Map::Map(){
	ground = "ground";
	object = "object";
}

void Map::initialize(){
	for(unsigned int j=0;j<GetPrivateProfileIntA("GROUND_TEXTURE_LIST", "numberOfGroundTextures", 1, "ini/mapTextures.ini");j++){
		itoa(j, tmpChar, 10);
		ground.push_back(tmpChar[0]);
		GetPrivateProfileStringA("GROUND_TEXTURE_LIST", ground.c_str(), "NOT_FOUND", tmpString, 100, "ini/mapTextures.ini");
		ground.pop_back();
		tmpTexture.loadFromFile(tmpString);
		groundTextures.push_back(tmpTexture);
	}

	for(unsigned int i=0;i<GetPrivateProfileIntA("OBJECT_TEXTURE_LIST", "numberOfObjectTextures", 1, "ini/mapTextures.ini");i++){
		itoa(i, tmpChar, 10);
		object.push_back(tmpChar[0]);
		GetPrivateProfileStringA("OBJECT_TEXTURE_LIST", object.c_str(), "NOT_FOUND", tmpString, 100, "ini/mapTextures.ini");
		object.pop_back();
		tmpTexture.loadFromFile(tmpString);
		objectTextures.push_back(tmpTexture);
	}
}

void Map::load(const char* MAPNAME){
	loadMapName = MAPNAME;
	loadMapName.insert(loadMapName.size(), ".ground");
	printf("%s\n", loadMapName.c_str());
	loadMap = fopen(loadMapName.c_str(), "rt");
	while(!feof(loadMap)){
		fscanf(loadMap, "%f %f %d %d %d %d %d\n", &tmpData_posX, &tmpData_posY, &tmpData_left, &tmpData_width, &tmpData_top, &tmpData_height, &tmpData_textureNum);
		tmpSprite.setPosition(tmpData_posX, tmpData_posY);
		tmpRect.left = tmpData_left;tmpRect.width = tmpData_width;tmpRect.top = tmpData_top;tmpRect.height = tmpData_height;
		tmpSprite.setTextureRect(tmpRect);
		tmpSprite.setTexture(groundTextures[tmpData_textureNum]);
		groundSprites.push_back(tmpSprite);
	}
	fclose(loadMap);

	loadMapName = MAPNAME;
	loadMapName.insert(loadMapName.size(), ".object");
	printf("%s\n", loadMapName.c_str());
	loadMap = fopen(loadMapName.c_str(), "rt");
	while(!feof(loadMap)){
		fscanf(loadMap, "%f %f %d %d %d %d %d\n", &tmpData_posX, &tmpData_posY, &tmpData_left, &tmpData_width, &tmpData_top, &tmpData_height, &tmpData_textureNum);
		tmpSprite.setPosition(tmpData_posX, tmpData_posY);
		tmpRect.left = tmpData_left;tmpRect.width = tmpData_width;tmpRect.top = tmpData_top;tmpRect.height = tmpData_height;
		tmpSprite.setTextureRect(tmpRect);
		tmpSprite.setTexture(objectTextures[tmpData_textureNum]);
		objectSprites.push_back(tmpSprite);
	}
	fclose(loadMap);

	loadMapName = MAPNAME;
	loadMapName.insert(loadMapName.size(), ".col");
	printf("%s\n", loadMapName.c_str());
	loadMap = fopen(loadMapName.c_str(), "rt");
	while(!feof(loadMap)){
		fscanf(loadMap, "%d %d %d %d\n", &tmpData_left, &tmpData_width, &tmpData_top, &tmpData_height);
		tmpRect.left = tmpData_left;tmpRect.width = tmpData_width;tmpRect.top = tmpData_top;tmpRect.height = tmpData_height;
		collideRects.push_back(tmpRect);
	}
	fclose(loadMap);
}
	

void Map::ground_Draw(sf::RenderWindow &window){
	for(int i=0;i<groundSprites.size();i++){
		window.draw(groundSprites[i]);
	}
}

void Map::object_Draw(sf::RenderWindow &window){
	for(int i=0;i<objectSprites.size();i++){
		window.draw(objectSprites[i]);
	}
}
