#include "shaderscene.h"

ShaderScene::ShaderScene() : mousePosition(0.0f,0.0f){
	texture.loadFromFile("img/parrot.png");
	shader.loadFromFile("shaders/shader.glsl", sf::Shader::Fragment);
	shader.setParameter("texture", texture);
	shader.setParameter("center",sf::Vector2f(mousePosition));
	sprite.setTexture(texture);


}

ShaderScene::~ShaderScene(){
}

void ShaderScene::update(sf::Event &event){
	shader.setParameter("center",sf::Vector2f(mousePosition));

}

void ShaderScene::draw(sf::RenderWindow &window){
	mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	mousePosition.x/=window.getSize().x;
	mousePosition.y/=window.getSize().y;
	window.draw(sprite, &shader);
}