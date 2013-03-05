#ifndef __shaderscene__
#define __shaderscene__

#include "stdafx.h"
#include "scenebase.h"

class ShaderScene : public SceneBase{
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		sf::Shader shader;

		sf::Vector2f mousePosition;

	public:
		ShaderScene();
		virtual ~ShaderScene();
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);

};

#endif