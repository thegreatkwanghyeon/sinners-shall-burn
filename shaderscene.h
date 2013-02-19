#ifndef __shaderscene__
#define __shaderscene__

#include "scenebase.h"

class ShaderScene : public SceneBase{
	private:

	public:
		ShaderScene();
		virtual ~ShaderScene();
		virtual void update();
		virtual void draw(sf::RenderWindow &window);

};

#endif