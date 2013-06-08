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
		 Vector2d plane; //촬영용 카메라의 2D 버전
		 Vector2d pos;
		 double time; //현재 프레임의 시간
		 double oldTime; //바로전 프레임의 시간
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

		 double moveSpeed; //상수는 squares/second
		 double rotSpeed; //상수는 radians/second

		 //texture rendering 관련 변수들

		 sf::Uint32 color;
		 sf::Uint8 buffer[1280*720*4];
		 std::vector<sf::Uint32> texture[8];
		 sf::RectangleShape point;
		 sf::Image drawingBuffer;
		 sf::Texture drawingTex;
		 sf::Sprite drawingSprite;
		 sf::Image textureImage;

		 //floor casting 관련 변수
		 Vector2d floorWall;
		 Vector2d currentFloor;
		 sf::Vector2i floorTex;
		 double weight;
		 double distWall;
		 double distPlayer;
		 double currentDist;

		 //이동관련변수
		 //sf::Vector2i player;
		 int isTurnL,isTurnR,isGoF,isGoR;
		 bool pressW,pressS,pressD,pressA;
		 sf::Clock deltaClock;
		 sf::Time currentTime;

		 //Image Loading 관련 함수, 이 레이캐스팅에서는 SDL 스타일로 image를 불러와야한다
		 std::vector<sf::Uint32> convertImageToTexture(sf::Image image);


	public:
		RayCastingScene();
		~RayCastingScene(){}
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		
};

#endif