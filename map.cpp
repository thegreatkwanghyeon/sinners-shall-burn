#include "map.h"

Map::Map(){
	ground = "ground";
	object = "object";
}

void Map::initialize(){
	mapTextureList.LoadFile("xmls/map_texture_list.xml");
	pNode = mapTextureList.FirstChild("Ground");
	pNode->ToElement()->Attribute("num", &num);
	pNode = pNode->FirstChild("TEXTURE");
	for(int i=0;i<num;i++){
		tmpTexture.loadFromFile(pNode->ToElement()->GetText());
		groundTextures.push_back(tmpTexture);
		pNode->NextSibling();
	}
	
	pNode = mapTextureList.FirstChild("Object");
	pNode->ToElement()->Attribute("num", &num);
	pNode = pNode->FirstChild("TEXTURE");
	for(int i=0;i<num;i++){
		tmpTexture.loadFromFile(pNode->ToElement()->GetText());
		objectTextures.push_back(tmpTexture);
		pNode->NextSibling();
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
		fscanf(loadMap, "%f %f %f %f\n", &float_tmpData_left, &float_tmpData_width, &float_tmpData_top, &float_tmpData_height);
		tmpCollideRect.left = float_tmpData_left;tmpCollideRect.width = float_tmpData_width;tmpCollideRect.top = float_tmpData_top;tmpCollideRect.height = float_tmpData_height;
		collideRects.push_back(tmpCollideRect);
	}
	fclose(loadMap);

	loadMapName = MAPNAME;
	loadMapName.insert(loadMapName.size(), ".dep");
	printf("%s\n", loadMapName.c_str());
	loadMap = fopen(loadMapName.c_str(), "rt");
	while(!feof(loadMap)){
		fscanf(loadMap, "%f %f %f %f\n", &float_tmpData_left, &float_tmpData_width, &float_tmpData_top, &float_tmpData_height);
		tmpCollideRect.left = float_tmpData_left;tmpCollideRect.width = float_tmpData_width;tmpCollideRect.top = float_tmpData_top;tmpCollideRect.height = float_tmpData_height;
		depthRects.push_back(tmpCollideRect);
		printf("%f\n", depthRects[0].left);
	}
	fclose(loadMap);
}
	
bool Map::isDepth(sf::Sprite sprite){
	for(int i=0;i<depthRects.size();i++){
		if(sprite.getGlobalBounds().intersects(depthRects[i]) && sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > depthRects[i].top + depthRects[i].height)
			return false;
	}
	return true;
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
