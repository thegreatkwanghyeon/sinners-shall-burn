#ifndef __raycastingscene__
#define __raycastingscene__

#define mapWidth 24
#define mapHeight 24

#include "scenebase.h"

class RayCastingScene : public SceneBase{
	private:
		int worldMap[mapWidth][mapHeight];

		int height, width, x;

		 sf::Vector2f dir;
		 sf::Vector2f plane; //�Կ��� ī�޶��� 2D ����
		 sf::Vector2f pos;
		 double time; //���� �������� �ð�
		 double oldTime; //�ٷ��� �������� �ð�
		 double cameraX;
		 sf::Vector2f rayPos;
		 sf::Vector2f rayDir;
		 sf::Vector2i map;
		 sf::Vector2f sideDist;
		 sf::Vector2f deltaDist;
		 double perpWallDist;
		 sf::Vector2i step;
		 int hit;
		 int side;

		 int lineHeight;
		 int drawStart;
		 int drawEnd;

		 double moveSpeed; //����� squares/second
		 double rotSpeed; //����� radians/second

		 sf::Color color;

		 void verLine(int x, int y1, int y2, sf::Color color, sf::RenderWindow &window);
		 sf::Color setRGB(sf::Color color);

	public:
		RayCastingScene();
		~RayCastingScene(){}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		
};

#endif