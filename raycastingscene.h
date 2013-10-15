//��Ʋ���� : ��Ʋ�� ����. ���� �̵�.

#ifndef __raycastingscene__
#define __raycastingscene__

#define texWidth 256
#define texHeight 256

#define screenWidth 640
#define screenHeight 360

#define FootStep 1
#define CntTime 0.2
#define Devide 10

#define numSprites 100

#include "scenebase.h"
#include "makemap.h"
#include "enemy.h"

class RayCastingScene{

	typedef sf::Vector2<double> Vector2d;

	private:
		int height, width, x;

		 Vector2d dir;
		 Vector2d plane; //�Կ��� ī�޶��� 2D ����
		 Vector2d pos;
		 double newTime; //���� �������� �ð�
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
		 std::vector<sf::Uint32> texture[9];
		 sf::RectangleShape point;
		 sf::Image drawingBuffer;
		 sf::Texture drawingTex,compassTexture;
		 sf::Sprite drawingSprite,compass;
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
		 int isTurnL,isTurnR,isGoF,isGoB, isGoR,isGoL;
		 bool pressW,pressS,pressD,pressA,pressL,pressR;
		 sf::Clock deltaClock;
		 sf::Time currentTime;

		 //�ʰ��ú���
		int worldMap[MapY+100][MapX+100];
		MakeMap *makemap;

		sf::RectangleShape rec;
		int fog[MapY+100][MapX+100];
		int fov;//�þ� ����
		//int angle,tempAngle;//����. 1,2,3,4;
		int getAngle();
		

		 //Image Loading ���� �Լ�, �� ����ĳ���ÿ����� SDL ��Ÿ�Ϸ� image�� �ҷ��;��Ѵ�
		 std::vector<sf::Uint32> convertImageToTexture(sf::Image image);

		 //��������Ʈ ���� ����
		 
		 struct Sprite{
			 double x;
			 double y;
			 int texture;
		 };

		 //���̵� ���� ����
		 sf::Shader sight;

		 Sprite sprite[numSprites];
		 double ZBuffer[screenWidth];
		 int spriteOrder[numSprites];
		 double spriteDistance[numSprites];
		 void combSort(int* order, double* dist, int amount);
		 double fixErrorNum(double num, double st, double ed, double setNum);


		 void setShader(const std::string &shader);
		 

		 //enemy ���� 
		 std::vector <Enemy*> *pEnemy;
		 size_t countEnemy; //enemy ������ ũ��



	public:
		RayCastingScene();
		~RayCastingScene();
		void update(sf::Event &event);
		void draw(sf::RenderWindow &window);
		int isBattle();
		//int getAngle();

		int getFOV();
		void setFOV(int _fov);
		
		//enemy ����
		void setEnemies(std::vector <Enemy*> *pEnemy);

};

#endif