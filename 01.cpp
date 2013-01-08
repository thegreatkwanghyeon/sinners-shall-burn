#include <SFML/Graphics.hpp>

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Texture texture;
	texture.loadFromFile("omg.jpg");
	sf::Sprite background;
	background.setTexture(texture);
sf::View standard = window.getView();
unsigned int size = 100;
sf::View minimap(sf::FloatRect(standard.getCenter().x, standard.getCenter().y, size, window.getSize().y*size/window.getSize().x));
minimap.setViewport(sf::FloatRect(1.f-(1.f*minimap.getSize().x)/window.getSize().x-0.02f, 1.f-(1.f*minimap.getSize().y)/window.getSize().y-0.02f, (1.f*minimap.getSize().x)/window.getSize().x, (1.f*minimap.getSize().y)/window.getSize().y));
minimap.zoom(4.f);
while (window.isOpen()){
	sf::Event event;
while (window.pollEvent(event)){
if (event.type == sf::Event::Closed)
	window.close();
}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		minimap.move(-0.1,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		minimap.move(0.1,0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		minimap.move(0,-0.1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		minimap.move(0,0.1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		minimap.zoom(0.999);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		minimap.zoom(1.001);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		minimap.rotate(0.1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		minimap.rotate(-0.1);
	}
	window.clear();
window.setView(standard);
window.draw(background);
window.setView(minimap);
window.draw(background);
	window.display();
}

return 0;
}