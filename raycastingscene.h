//배틀관련 : 배틀용 변수. 차후 이동.

#ifndef __raycastingscene__
#define __raycastingscene__

#define texWidth 64
#define texHeight 64

#define screenWidth 640
#define screenHeight 360

#define FootStep 1
#define CntTime 0.2
#define Devide 10

#define numSprites 1

#include "scenebase.h"
#include "makemap.h"
#include "enemy.h"

class RayCastingScene{

	typedef sf::Vector2<double> Vector2d;

	private:
		int height, width, x;

		 Vector2d dir;
		 Vector2d plane; //촬영용 카메라의 2D 버전
		 Vector2d pos;
		 double newTime; //현재 프레임의 시간
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
		 std::vector<sf::Uint32> texture[9];
		 sf::RectangleShape point;
		 sf::Image drawingBuffer;
		 sf::Texture drawingTex,compassTexture;
		 sf::Sprite drawingSprite,compass;
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
		 int isTurnL,isTurnR,isGoF,isGoB, isGoR,isGoL;
		 bool pressW,pressS,pressD,pressA,pressL,pressR;
		 sf::Clock deltaClock;
		 sf::Time currentTime;

		 //맵관련변수
		int worldMap[MapY+100][MapX+100];
		MakeMap *makemap;

		sf::RectangleShape rec;
		int fog[MapY+100][MapX+100];
		int fov;//시야 변수
		int angle,tempAngle;//각도. 1,2,3,4;
		

		 //Image Loading 관련 함수, 이 레이캐스팅에서는 SDL 스타일로 image를 불러와야한다
		 std::vector<sf::Uint32> convertImageToTexture(sf::Image image);

		 //스프라이트 관련 변수
		 
		 struct Sprite{
			 double x;
			 double y;
			 int texture;
		 };

		 //쉐이딩 관련 변수
		 sf::Shader sight;

		 Sprite sprite[numSprites];
		 int monsterNum[numSprites];//스프라이트들의 몬스터 번호를 따로 저장해줌.
		 double ZBuffer[screenWidth];
		 int spriteOrder[numSprites];
		 double spriteDistance[numSprites];
		 void combSort(int* order, double* dist, int amount);
		 double fixErrorNum(double num, double st, double ed, double setNum);


		 void setShader(const std::string &shader);
		 

		 //enemy 관련 
		 std::vector <Enemy*> *pEnemy;
		 size_t countEnemy; //enemy 벡터의 크기



	public:
		RayCastingScene();
		~RayCastingScene();
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		int isBattle();
		//int getAngle();

		int getFOV();
		void setFOV(int _fov);
		
		//enemy 관련
		void setEnemies(std::vector <Enemy*> *pEnemy);

};

#endif