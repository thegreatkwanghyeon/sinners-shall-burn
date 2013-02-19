#include "global.h"
#include <SFML/Graphics.hpp>
#include "ui.h"
#include "layer.h"
#include "collide.h"

int main(void){

	std::string MAPNAME;
	std::string ground = ".groud";
	std::string object = ".object";
	std::string collide = ".col";
	bool gridView = false;
	bool viewAll = false;
	int currentTexture = 0;
	int currentLayer = 0;

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	initialize();

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::Sprite mainSprite;
	mainSprite.setPosition(TEXTUREPOSX, 0);
	mainSprite.setTexture(textures[currentLayer][currentTexture]);	

//-------------------------------------------------------------------------------------------------------------------------------------------------------
	
	sf::Texture gridTexture;
	sf::Texture mapGrid;

	sf::Sprite mapGridSprite;
	sf::Sprite gridSprite;
	
	gridTexture.loadFromFile("tiles/grid.png");	
	mapGrid.loadFromFile("tiles//map_grid.png");

	gridSprite.setPosition(TEXTUREPOSX, 0);
	gridSprite.setTexture(gridTexture);

	mapGridSprite.setTexture(mapGrid);

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	UI ui;
	Collide collideLayer;
	collideLayer.initialize();

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	printf("Enter a filename to be saved\n");
	scanf("%s",MAPNAME.c_str());
	ground.insert(0, MAPNAME.c_str());
	object.insert(0, MAPNAME.c_str());
	collide.insert(0, MAPNAME.c_str());

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::Font font;
	font.loadFromFile("font/TheKingsoftheHouse-Regular.ttf");

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::Text currentLayerText;
	currentLayerText.setFont(font);
	currentLayerText.setPosition(10, MAPHEIGHT + 20);
	currentLayerText.setString(ground);	

	sf::Text currentTextureText;
	currentTextureText.setFont(font);
	currentTextureText.setPosition(10, MAPHEIGHT + 80);
	currentTextureText.setString(texturePaths[currentLayer][currentTexture]);	

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	Layer groundLayer(ground);
	Layer objectLayer(object);
	groundLayer.setTexture(currentTexture, MAPTILEWIDTH, MAPTILEHEIGHT, 0);
	objectLayer.setTexture(currentTexture, OBJECTTILEWIDTH, OBJECTTILEHEIGHT, 1);
	groundLayer.save();
	objectLayer.save();
	collideLayer.save(collide);

	printf("Left click : Put tile\nRight click : Remove tile, select tile\nG : Show grid\nF : Hide grid\nUp, Down : Change tileset\nNum 1, 2 : groundLayer, objectLayer\nA : View All Layer\nView current layer\nS : Save\nESC : Exit program\n");

	sf::RenderWindow editorWindow(sf::VideoMode(MAPWIDTH + 500, MAPHEIGHT + 150), "Tile Map Editor");	
	editorWindow.setKeyRepeatEnabled(false);

	while(editorWindow.isOpen()){
		sf::Event Event;
		while (editorWindow.pollEvent(Event)){
			if(Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				editorWindow.close();
			}

//-------------------------------------------------------------------------------------------------------------------------------------------------------			
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
			currentLayer = 0;
			currentTexture = 0;
			currentLayerText.setString(ground);
			mainSprite.setTexture(textures[currentLayer][currentTexture]);	
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
			currentLayer = 1;		
			currentTexture = 0;			
			currentLayerText.setString(object);
			mainSprite.setTexture(textures[currentLayer][currentTexture]);	
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
			currentLayer = 2;
			viewAll = true;
			currentLayerText.setString(collide);
		}

		if(currentLayer == 0){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentTexture < MAXMAPTEXTURES - 1){
				++currentTexture;
				groundLayer.setTexture(currentTexture, MAPTILEWIDTH, MAPTILEHEIGHT, currentLayer);	
				mainSprite.setTexture(textures[currentLayer][currentTexture]);
				printf("%d\n", currentTexture);
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentTexture > 0){
				--currentTexture;
				groundLayer.setTexture(currentTexture, MAPTILEWIDTH, MAPTILEHEIGHT, currentLayer);
				mainSprite.setTexture(textures[currentLayer][currentTexture]);
				printf("%d\n", currentTexture);
			}
		}

		if(currentLayer == 1){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentTexture < MAXOBJECTTEXTURES - 1){
				++currentTexture;
				objectLayer.setTexture(currentTexture, OBJECTTILEWIDTH, OBJECTTILEHEIGHT, currentLayer);			
				mainSprite.setTexture(textures[currentLayer][currentTexture]);
				printf("%d\n", currentTexture);
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentTexture > 0){
				--currentTexture;
				objectLayer.setTexture(currentTexture, OBJECTTILEWIDTH, OBJECTTILEHEIGHT, currentLayer);
				mainSprite.setTexture(textures[currentLayer][currentTexture]);
				printf("%d\n", currentTexture);
			}
		}		

//-------------------------------------------------------------------------------------------------------------------------------------------------------			

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			gridView = true;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			gridView = false;		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			viewAll = true;

		if(currentLayer !=2 && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			viewAll = false;		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			groundLayer.save();
			objectLayer.save();
			collideLayer.save(collide);
		}

//-------------------------------------------------------------------------------------------------------------------------------------------------------

		editorWindow.clear();

//-------------------------------------------------------------------------------------------------------------------------------------------------------		


		if(viewAll){
			if(currentLayer == 0){
				groundLayer.draw(editorWindow);
				objectLayer.draw(editorWindow);
				groundLayer.update(editorWindow, Event);
			}

			if(currentLayer == 1){
				groundLayer.draw(editorWindow);
				objectLayer.draw(editorWindow);
				objectLayer.update(editorWindow, Event);
			}

			if(currentLayer == 2){
				groundLayer.draw(editorWindow);
				objectLayer.draw(editorWindow);
				collideLayer.check(sf::Mouse::getPosition(editorWindow).x, sf::Mouse::getPosition(editorWindow).y);
				collideLayer.draw(editorWindow);
			}				
		}
		else {
			if(currentLayer == 0){
				groundLayer.draw(editorWindow);
				groundLayer.update(editorWindow, Event);
			}
			if(currentLayer == 1){
				objectLayer.draw(editorWindow);
				objectLayer.update(editorWindow, Event);
			}
		}

	

		ui.draw(editorWindow);

		editorWindow.draw(mainSprite);	
		editorWindow.draw(gridSprite);	

		if(gridView)
			editorWindow.draw(mapGridSprite);

		editorWindow.draw(currentLayerText);
		if(currentLayer != 2)
			currentTextureText.setString(texturePaths[currentLayer][currentTexture]);
		editorWindow.draw(currentTextureText);



//-------------------------------------------------------------------------------------------------------------------------------------------------------		

		editorWindow.display();			
	}
}
	return EXIT_SUCCESS;
}