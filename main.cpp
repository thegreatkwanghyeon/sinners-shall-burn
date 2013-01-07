#include <SFML/Graphics.hpp>

int main()
{
int x=0,y=0;
sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
sf::Texture texture;

texture.loadFromFile("omg.jpg");

sf::IntRect subRect;
subRect.left = 0;
subRect.top = 0;
subRect.width = 80;
subRect.height = 80;
sf::Sprite sprite(texture, subRect);
sf::CircleShape shape;
shape.setPosition(100,100);
shape.setRadius(1000);
shape.setFillColor(sf::Color(255,200,100,150));
 sf::ConvexShape polygon;
 polygon.setPointCount(3);
 polygon.setPoint(0, sf::Vector2f(0, 0));
 polygon.setPoint(1, sf::Vector2f(0, 100));
 polygon.setPoint(2, sf::Vector2f(25, 50));
 polygon.setOutlineColor(sf::Color::Cyan);
 polygon.setOutlineThickness(5);
 polygon.setPosition(10, 20);
 polygon.setFillColor(sf::Color::Red);
 sf::Image img;

while (window.isOpen())
{
sf::Event event;
while (window.pollEvent(event))
{
if (event.type == sf::Event::Closed)
window.close();
}

if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
subRect.left++;
x++;
}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
subRect.left--;
x--;
}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
subRect.top--;
y--;
}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
subRect.top++;
y++;
}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
	img = window.capture();
	img.saveToFile("a.jpg");
	window.setTitle("a");
}

sprite.setTextureRect(subRect);
sprite.setPosition(x,y);

window.clear();
window.draw(sprite);
window.draw(shape);
window.draw(polygon);
window.display();
}

return 0;
}