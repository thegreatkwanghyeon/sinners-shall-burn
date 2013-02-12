#include "global.h"
#include <SFML/Graphics.hpp>
#include "ui.h"
#include "layer.h"

int main(void){
	
	std::string MAPNAME;
	bool gridView = false;

	sf::Texture mainTexture;
	sf::Texture gridTexture;
	sf::Texture mapGrid;

	sf::Sprite mapGridSprite;
	sf::Sprite mainSprite;
	sf::Sprite gridSprite;

	mainTexture.loadFromFile("tiles/prairie.png");
	gridTexture.loadFromFile("tiles/grid.png");	
	mapGrid.loadFromFile("tiles//map_grid.png");
	
	mainSprite.setPosition(TEXTUREPOSX, 0);
	mainSprite.setTexture(mainTexture);

	gridSprite.setPosition(TEXTUREPOSX, 0);
	gridSprite.setTexture(gridTexture);

	mapGridSprite.setTexture(mapGrid);

	UI ui;

	printf("Enter a filename to be saved\n");
	scanf("%s",MAPNAME.c_str());

	Layer groundLayer(MAPNAME);
	groundLayer.setTexture("tiles/prairie.png");

	printf("Left click : Put tile\nRight click : Remove tile, select tile\nG : Show grid\nC : Hide grid\nS : Save\nESC : Exit program\n");

	sf::RenderWindow editorWindow(sf::VideoMode(MAPWIDTH + mainTexture.getSize().x + 15, MAPHEIGHT), "Tile Map Editor");	

	while(editorWindow.isOpen()){
		sf::Event Event;
		while (editorWindow.pollEvent(Event)){
			if(Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				editorWindow.close();
			}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			gridView = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			gridView = false;		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			groundLayer.save();

		editorWindow.clear();
		ui.draw(editorWindow);
		editorWindow.draw(mainSprite);	
		editorWindow.draw(gridSprite);	
		groundLayer.update(editorWindow);
		groundLayer.draw(editorWindow);
		if(gridView)
			editorWindow.draw(mapGridSprite);
		editorWindow.display();			
	}
}
	return EXIT_SUCCESS;
}