#include <SFML/Graphics.hpp>

int main(){
	float zoom = 1.0,rotate = 0.0,x = 0.0,y=0.0;
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
		x-=0.001;
		minimap.move(x,y);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		x+=0.001;
		minimap.move(x,y);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		y-=0.001;
		minimap.move(x,y);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		y+=0.001;
		minimap.move(x,y);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		zoom-=0.0001;
		minimap.zoom(zoom);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		zoom+=0.0001;
		minimap.zoom(zoom);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		rotate-=0.01;
		minimap.rotate(rotate);

	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		rotate+=0.01;
		minimap.rotate(rotate);
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