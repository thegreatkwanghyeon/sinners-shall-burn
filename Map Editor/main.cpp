#include "global.h"
#include <SFML/Graphics.hpp>
#include "ui.h"
#include "layer.h"

int main(void){
	printf("Left click : Put tile\nRight click : Remove tile, select tile\nG : View grid\nC : Off grid\nESC : Exit program\n");
	bool gridView = false;

	sf::Texture mainTexture;
	mainTexture.loadFromFile("tiles/prairie.png");

	sf::Texture gridTexture;
	gridTexture.loadFromFile("tiles/grid.png");

	sf::Texture mapGrid;
	mapGrid.loadFromFile("tiles//map_grid.png");

	sf::Sprite mainSprite;
	mainSprite.setTexture(mainTexture);
	sf::Sprite gridSprite;
	gridSprite.setTexture(gridTexture);
	sf::Sprite mapGridSprite;
	mapGridSprite.setTexture(mapGrid);

	UI ui;
	Layer groundLayer;
	groundLayer.setTexture(mainTexture);

	sf::RenderWindow editorWindow(sf::VideoMode(MAPWIDTH + mainTexture.getSize().x + 15, MAPHEIGHT), "Tile Map Editor");	

	mainSprite.setPosition(TEXTUREPOSX, 0);
	gridSprite.setPosition(TEXTUREPOSX, 0);

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