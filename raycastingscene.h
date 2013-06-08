#ifndef __raycastingscene__
#define __raycastingscene__

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64

#define Footstep 1
#define cntTime 0.2
#define DEVIDE 10

#include "scenebase.h"

class RayCastingScene : public SceneBase{

	typedef sf::Vector2<double> Vector2d;

	private:
		int worldMap[mapWidth][mapHeight];

		int height, width, x;

		 Vector2d dir;
		 Vector2d plane; //�Կ��� ī�޶��� 2D ����
		 Vector2d pos;
		 double time; //���� �������� �ð�
		 double oldTime; //�ٷ��� �������� �ð�
		 double cameraX;
		 Vector2d rayPos;
		 Vector2d rayDir;
		 sf::Vector2i map;
		 Vector2d sideDist;
		 Vector2d deltaDist;
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
		 sf::Uint8 buffer[1280*720*4];
		 std::vector<sf::Uint32> texture[8];
		 sf::RectangleShape point;
		 sf::Image drawingBuffer;
		 sf::Texture drawingTex;
		 sf::Sprite drawingSprite;
		 sf::Image textureImage;

		 //floor casting ���� ����
		 Vector2d floorWall;
		 Vector2d currentFloor;
		 sf::Vector2i floorTex;
		 double weight;
		 double distWall;
		 double distPlayer;
		 double currentDist;

		 //�̵����ú���
		 //sf::Vector2i player;
		 int isTurnL,isTurnR,isGoF,isGoR;
		 bool pressW,pressS,pressD,pressA;
		 sf::Clock deltaClock;
		 sf::Time currentTime;

		 //Image Loading ���� �Լ�, �� ����ĳ���ÿ����� SDL ��Ÿ�Ϸ� image�� �ҷ��;��Ѵ�
		 std::vector<sf::Uint32> convertImageToTexture(sf::Image image);


	public:
		RayCastingScene();
		~RayCastingScene(){}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		
};

#endif