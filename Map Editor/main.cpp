#include "global.h"
#include <SFML/Graphics.hpp>
#include "ui.h"
#include "layer.h"

int main(void){

	std::string MAPNAME;
	std::string ground = ".groud";
	std::string object = ".object";
	bool gridView = false;
	int currentTexture = 0;
	int currentLayer = 0;

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	initialize();

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::Sprite mainSprite;
	mainSprite.setPosition(TEXTUREPOSX, 0);
	mainSprite.setTexture(textures[currentTexture]);	

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

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	printf("Enter a filename to be saved\n");
	scanf("%s",MAPNAME.c_str());
	ground.insert(0, MAPNAME.c_str());
	object.insert(0, MAPNAME.c_str());

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
	currentTextureText.setString(texturePaths[currentTexture]);	

//-------------------------------------------------------------------------------------------------------------------------------------------------------

	Layer groundLayer(ground);
	Layer objectLayer(object);
	groundLayer.setTexture(currentTexture);
	objectLayer.setTexture(currentTexture);
	groundLayer.save();
	objectLayer.save();

	printf("Left click : Put tile\nRight click : Remove tile, select tile\nG : Show grid\nC : Hide grid\nUp, Down : Change tileset\nNum 1, 2 : groundLayer, objectLayer\nS : Save\nESC : Exit program\n");

	sf::RenderWindow editorWindow(sf::VideoMode(MAPWIDTH + textures[currentTexture].getSize().x + 15, MAPHEIGHT + 150), "Tile Map Editor");	
	editorWindow.setKeyRepeatEnabled(false);

	while(editorWindow.isOpen()){
		sf::Event Event;
		while (editorWindow.pollEvent(Event)){
			if(Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				editorWindow.close();
			}

//-------------------------------------------------------------------------------------------------------------------------------------------------------			
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentTexture < MAXTEXTURES-1){
			++currentTexture;
			groundLayer.setTexture(currentTexture);
			objectLayer.setTexture(currentTexture);
			mainSprite.setTexture(textures[currentTexture]);	
			printf("%d\n",currentTexture);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentTexture > 0){
			--currentTexture;
			groundLayer.setTexture(currentTexture);
			objectLayer.setTexture(currentTexture);
			mainSprite.setTexture(textures[currentTexture]);				
			printf("%d\n",currentTexture);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
			currentLayer = 0;
			currentLayerText.setString(ground);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
			currentLayer = 1;
			currentLayerText.setString(object);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			gridView = true;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			gridView = false;		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			groundLayer.save();
			objectLayer.save();
		}

//-------------------------------------------------------------------------------------------------------------------------------------------------------

		editorWindow.clear();

//-------------------------------------------------------------------------------------------------------------------------------------------------------		

		ui.draw(editorWindow);
		editorWindow.draw(mainSprite);	
		editorWindow.draw(gridSprite);	
		if(currentLayer == 0){
			groundLayer.update(editorWindow);
			groundLayer.draw(editorWindow);
		}
		if(currentLayer == 1){
			objectLayer.update(editorWindow);
			objectLayer.draw(editorWindow);
		}

		if(gridView)
			editorWindow.draw(mapGridSprite);

		editorWindow.draw(currentLayerText);
		currentTextureText.setString(texturePaths[currentTexture]);
		editorWindow.draw(currentTextureText);

//-------------------------------------------------------------------------------------------------------------------------------------------------------		

		editorWindow.display();			
	}
}
	return EXIT_SUCCESS;
}