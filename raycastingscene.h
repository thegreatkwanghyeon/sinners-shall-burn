#ifndef __raycastingscene__
#define __raycastingscene__

#define mapWidth 24
#define mapHeight 24
#define texWidth 256
#define texHeight 256

#define Footstep 1

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

		 //texture rendering ���� ������

		 sf::Uint32 color;
		 sf::Uint8 realBuffer[1280*720*4];
		 std::vector<sf::Uint32> realTexture[8];
		 sf::RectangleShape point;
		 sf::Image drawingBuffer;
		 sf::Texture drawingTex;
		 sf::Sprite drawingSprite;

		 //�̵����ú���
		 //sf::Vector2i player;
		 int isTurnL,isTurnR,isGoF,isGoR;


	public:
		RayCastingScene();
		~RayCastingScene(){}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		
};

#endif