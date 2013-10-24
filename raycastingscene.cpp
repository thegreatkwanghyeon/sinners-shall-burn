#include "raycastingscene.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

RayCastingScene::RayCastingScene(){	
	/*makemap = new MakeMap();
	makemap->buildMap();*/
	for(int i=0;i<MapY;i++){
		for(int j=0;j<MapX;j++){
			worldMap[i][j]=0;//혹시 몰라서 해놓은 디폴트.
			fog[i][j]=1;
		}
	}


	height = screenHeight;
	width = screenWidth;
		
	pos.x = 2.5; 
	pos.y = 2.5;
	dir.x = 0; 
	dir.y = -1;
	plane.x = -0.66; 
	plane.y = 0;

	//---이동---//
	//player.x = 1.5;
	//player.y = 1.5;
	isTurnL=0;
	isTurnR=0;
	isGoF=0;
	isGoB=0;

	pressS=false;
	pressW=false;
	pressA=false;
	pressD=false;

	deltaClock.restart();
	//---
  
	newTime = 0;
	oldTime = 0;

	moveSpeed = 1/(float)Devide;
	rotSpeed = 1.575/(float)Devide;

	for(int i=0; i<8; i++){
		texture[i].resize(texWidth * texHeight);
	}

	  
	textureImage.loadFromFile("img/textures/redbrick.png");
	texture[0] = convertImageToTexture(textureImage);
	textureImage.loadFromFile("img/textures/stone.png");
	texture[1] = convertImageToTexture(textureImage);
	textureImage.loadFromFile("img/textures/stone.png");
	texture[2] = convertImageToTexture(textureImage);
	textureImage.loadFromFile("img/textures/stone.png");
	texture[3] = convertImageToTexture(textureImage);

	textureImage.loadFromFile("img/textures/stone.png");
	texture[4] = convertImageToTexture(textureImage);
	textureImage.loadFromFile("img/textures/stone.png");
	texture[5] = convertImageToTexture(textureImage);
	textureImage.loadFromFile("img/textures/stone.png");
	texture[6] = convertImageToTexture(textureImage);
	textureImage.loadFromFile("img/textures/stone.png");
	texture[7] = convertImageToTexture(textureImage);
	textureImage.loadFromFile("img/textures/eagle.png");
	texture[8] = convertImageToTexture(textureImage);//문짝(9)

	drawingBuffer.create(width,height,sf::Color::Black);

	//쉐이더
	sight.loadFromFile("shaders/darker.glsl",sf::Shader::Fragment);
	sight.setParameter("texture",drawingTex);
	sight.setParameter("center", sf::Vector2f(0.5, 0.5));

	rec.setSize(sf::Vector2f(10,10));

	fov=20;//디폴트. 천리안 등의 슼킬이나 템이 있으면 교체가능. 근데 딱히 하고싶지는 않음. 지도나 이런거 얻으면 범위 25로 해서 맵핵모드 할까 고민중
}
RayCastingScene::~RayCastingScene(){
	//delete makemap;
}

void RayCastingScene::setMap(int _map[][MapX+100]){
	for(int i=0;i<MapY;i++){
		for(int j=0;j<MapX;j++){
			worldMap[i][j]=_map[i][j];
			fog[i][j]=1;
		}
	}
}

std::vector<sf::Uint32> RayCastingScene::convertImageToTexture(sf::Image image){
	sf::Color color;
	std::vector<sf::Uint32> texture;

	texture.resize(texWidth * texHeight);
	
	for(int x=0; x<texWidth; x++){
		for(int y=0; y<texHeight; y++){
			color = image.getPixel(x, y);
			texture[texWidth*y + x] = color.r * 65536 + color.g * 256 + color.b;	
		} 
	}
	return texture;
}

void RayCastingScene::update(sf::Event &event){
	int tempX, tempY;//좌우이동용 temp변수

	for(int i=pos.y-fov;i<=pos.y+fov;i++){
		for(int j=pos.x-fov;j<=pos.x+fov;j++){
			if(i < 0 || j < 0)
				continue;
			fog[i][j]=0;
		}
	}

	if(dir.x < 0.9 && dir.x > -0.9)
		if(dir.y < 0)
			tempX = -1;
		else
			tempX = 1;
	else
		tempX = 0;	
	//------
	if(dir.y < 0.9 && dir.y > -0.9)
		if(dir.x < 0)
			tempY = 1;
		else
			tempY = -1;
	else
		tempY = 0;
	//---

	if (isGoF == 0 && isGoB == 0 && isTurnL == 0 && isTurnR == 0){//현재 멈춰있는 상태(노 애니메이션)		
		if(pressW == false && worldMap[int(pos.x+dir.x)][int(pos.y+dir.y)] == false &&  sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			pressW=true;
			isGoF=Devide;
			//---
			deltaClock.restart();
		}
		if(pressS == false && worldMap[int(pos.x-dir.x)][int(pos.y-dir.y)] == false &&  sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			pressS=true;
			isGoB=Devide;
			//---
			deltaClock.restart();
		}
		//-----
		//---
		if(pressA == false && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			pressA=true;
			isTurnL=Devide;
			//---
			deltaClock.restart();
		}
		if(pressD == false && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			pressD=true;
			isTurnR=Devide;
			//---
			deltaClock.restart();
		}
		//---
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) == false)
			pressW=false;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) == false)
			pressS=false;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) == false)
			pressA=false;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) == false)
			pressD=false;
	}else{
		//float delta=deltaClock.getElapsedTime().asSeconds();
		//float current=currentTime.asSeconds();
		if(deltaClock.getElapsedTime().asSeconds() >= CntTime/Devide){
			if(isTurnR != 0){
				if(((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide)) > 1){
					rotSpeed*=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					isTurnR-=(int)((deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					if(isTurnR < 0){
						rotSpeed/=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
						isTurnR=0;
					}
				}else
					isTurnR--;
				//---
				double oldDirX = dir.x;
				dir.x = dir.x * cos(-rotSpeed) - dir.y * sin(-rotSpeed);
				dir.y = oldDirX * sin(-rotSpeed) + dir.y * cos(-rotSpeed);
				double oldplaneX = plane.x;
				plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
				plane.y = oldplaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);
			}else if(isTurnL != 0){
				if(((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide)) > 1){
					rotSpeed*=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					isTurnL-=(int)((deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					if(isTurnL < 0){
						rotSpeed/=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
						isTurnL=0;
					}
				}else
					isTurnL--;
				//---
				double oldDirX = dir.x;
				dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
				dir.y = oldDirX * sin(rotSpeed) + dir.y * cos(rotSpeed);
				double oldplaneX = plane.x;
				plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
				plane.y = oldplaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
			}else if(isGoF != 0){
				if(((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide)) > 1){
					moveSpeed*=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					isGoF-=(int)((deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					if(isGoF < 0){
						moveSpeed/=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
						isGoF=0;
					}
				}else
					isGoF--;
				pos.x += floor(dir.x+0.5) * moveSpeed;
				pos.y += floor(dir.y+0.5) * moveSpeed;
				/*
				if(isGoF == 0){
					pos.x=(int)pos.x+0.5;
					pos.y=(int)pos.y+0.5;
				}*/
			}else if(isGoB != 0){
				if(((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide)) > 1){
					moveSpeed*=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					isGoB-=(int)((deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
					if(isGoB < 0){
						moveSpeed/=((int)(deltaClock.getElapsedTime().asSeconds())/(CntTime/Devide));
						isGoB=0;
					}
				}else
					isGoB--;
				pos.x -= floor(dir.x+0.5) * moveSpeed;
				pos.y -= floor(dir.y+0.5) * moveSpeed;
				//---
				if(isGoB == 0){
					pos.x=(int)pos.x+0.5;
					pos.y=(int)pos.y+0.5;
				}
			}
			//printf("%.5lf %.5lf | %.5lf %.5lf ----   %.5lf\n",dir.x,dir.y,plane.x,plane.y,deltaClock.getElapsedTime().asSeconds());
			deltaClock.restart();
		}
		moveSpeed = 1/(double)Devide;
		rotSpeed = 1.575/(double)Devide;
	}
	//---
	

	dir.x=fixErrorNum(dir.x, -0.1, 0.1, 0.0);
	dir.y=fixErrorNum(dir.y, -0.1, 0.1, 0.0);

	dir.x=fixErrorNum(dir.x, 0.99, 1.1, 1.0);
	dir.y=fixErrorNum(dir.y, 0.99, 1.1, 1.0);

	dir.x=fixErrorNum(dir.x, -1.1, -0.99, -1.0);
	dir.y=fixErrorNum(dir.y, -1.1, -0.99, -1.0);
	//---
	plane.x=fixErrorNum(plane.x, -0.1, 0.1, 0.0);
	plane.y=fixErrorNum(plane.y, -0.1, 0.1, 0.0);

	plane.x=fixErrorNum(plane.x, 0.65, 0.67, 0.66);
	plane.y=fixErrorNum(plane.y, 0.65, 0.67, 0.66);

	plane.x=fixErrorNum(plane.x, -0.67, -0.65, -0.66);
	plane.y=fixErrorNum(plane.y, -0.67, -0.65, -0.66);
	//---

	/*
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		setShader((std::string)"blood");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
		setShader((std::string)"darker");
	}*/
}
double RayCastingScene::fixErrorNum(double num, double st, double ed, double setNum){
	if(num > st && num < ed)
		return setNum;
	return num;
}

//setShader 함수의 매개변수는 blood 이거나 darker 이여야합니다
void RayCastingScene::setShader(const std::string &shader){
	
	if(shader == "darker")
		sight.loadFromFile("shaders/darker.glsl",sf::Shader::Fragment);
	else if(shader == "blood")
		sight.loadFromFile("shaders/blood.glsl",sf::Shader::Fragment);
	sight.setParameter("texture",drawingTex);
	sight.setParameter("center", sf::Vector2f(0.5, 0.5));

}

void RayCastingScene::combSort(int* order, double* dist, int amount){
	int gap = amount;
  bool swapped = false;
  while(gap > 1 || swapped)
  {
    //shrink factor 1.3
    gap = (gap * 10) / 13;
    if(gap == 9 || gap == 10) gap = 11;
    if (gap < 1) gap = 1;
    swapped = false;
    for (int i = 0; i < amount - gap; i++)
    {
      int j = i + gap;
      if (dist[i] < dist[j])
      {
        std::swap(dist[i], dist[j]);
        std::swap(order[i], order[j]);
        swapped = true;
      }
    }
  }
}


void RayCastingScene::draw(sf::RenderWindow &window){
	sf::RectangleShape point;
	point.setSize(sf::Vector2f(1.0,1.0));

    for(x = 0; x < width; x++){
      cameraX = 2 * x / double(width) - 1;
      rayPos.x = pos.x;
      rayPos.y = pos.y;
      rayDir.x = dir.x + plane.x * cameraX;
      rayDir.y = dir.y + plane.y * cameraX;

      map.x = int(rayPos.x);
      map.y = int(rayPos.y);
      
      deltaDist.x = sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x));
      deltaDist.y = sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y));
	  
	  hit = 0;

      if (rayDir.x < 0){
        step.x = -1;
        sideDist.x = (rayPos.x - map.x) * deltaDist.x;
      }
      else{
        step.x = 1;
        sideDist.x = (map.x + 1.0 - rayPos.x) * deltaDist.x;
      }
      if (rayDir.y < 0){
        step.y = -1;
        sideDist.y = (rayPos.y - map.y) * deltaDist.y;
      }
      else{
        step.y = 1;
        sideDist.y = (map.y + 1.0 - rayPos.y) * deltaDist.y;
      }

      while (hit == 0){
        if (sideDist.x < sideDist.y){
          sideDist.x += deltaDist.x;
          map.x += step.x;
          side = 0;
        }
        else{
          sideDist.y += deltaDist.y;
          map.y += step.y;
          side = 1;
        }
        if (worldMap[map.x][map.y] > 0) hit = 1;
      } 

      if (side == 0)
		  perpWallDist = fabs((map.x - rayPos.x + (1 - step.x) / 2) / rayDir.x);
      else
		 perpWallDist = fabs((map.y - rayPos.y + (1 - step.y) / 2) / rayDir.y);

	  lineHeight = abs(int(height / perpWallDist));

      drawStart = -lineHeight / 2 + height / 2;

      if(drawStart < 0)drawStart = 0;
		 drawEnd = lineHeight / 2 + height / 2;

      if(drawEnd >= height)drawEnd = height - 1;

	  int texNum = worldMap[map.x][map.y] - 1;


	  //texture rendering 에 사용되는 코드
	  double wallX;
	  if(side == 1)
		  wallX = rayPos.x + ((map.y - rayPos.y + (1 - step.y) / 2) / rayDir.y) * rayDir.x;
	  else
		  wallX = rayPos.y + ((map.x - rayPos.x + (1 - step.x) / 2) / rayDir.x) * rayDir.y;

	  wallX -= floor(wallX);

	  int texX = int(wallX * double(texWidth));
	  if(side == 0 && rayDir.x > 0)
		  texX = texWidth - texX - 1;
	  if(side == 1 && rayDir.y < 0)
		  texX = texX = texWidth - texX -1;
	  

	  //퍼포먼스에 가장 영향을 많이 주는 부분 (이 for문이 부하가 가장 많다)
	  //특히 buffer 에 값을 대입할때
		for(int y = drawStart; y<drawEnd; y++){
		  
			int d = y * 256 - height * 128 + lineHeight * 128;
			int texY = ((d*texHeight)/lineHeight) / 256;
		  
			color = texture[texNum][texHeight * texY + texX];
		  
			if(side == 1)
				color = (color >> 1) & 8355711;
			 
			buffer[y*width*4 + x*4 + 2] = color%256;
			color >>=8;
			buffer[y*width*4 + x*4 + 1] = color%256;
			color >>=8;
			buffer[y*width*4 + x*4 + 0] = color%256;
			buffer[y*width*4 + x*4 + 3] = 255;  
		}
	  
	  //여기까지 texture rendering 이었습니다!

	  //스프라이트 캐스팅을 위한 ZBuffer 계산
      ZBuffer[x] = perpWallDist; //수직거리가 사용된다

	  //이제 floor rendering 이 시작됩니다!

	  if(side == 0 && rayDir.x > 0){
		  floorWall.x = map.x;
		  floorWall.y = map.y + wallX;
	  }else if(side ==0 && rayDir.x < 0){
		  floorWall.x = map.x + 1.0;
		  floorWall.y = map.y + wallX;
	  }else if(side == 1 && rayDir.y > 0){
		  floorWall.x = map.x + wallX;
		  floorWall.y = map.y;
	  }else{
		  floorWall.x = map.x + wallX;
		  floorWall.y = map.y + 1.0;
	  }

	  distWall = perpWallDist;
	  distPlayer = 0.0;

	  if(drawEnd < 0)
		  drawEnd = height;
	  
		for(int y = drawEnd ; y < height; y++){
			currentDist = height/(2.0*y-height);


			weight = (currentDist - distPlayer) / (distWall - distPlayer);
			currentFloor.x = weight * floorWall.x + (1.0 - weight) * pos.x;
			currentFloor.y = weight * floorWall.y + (1.0 - weight) * pos.y;

			floorTex.x = (int)(currentFloor.x * texWidth) % texWidth;
			floorTex.y = (int)(currentFloor.y * texHeight) % texHeight;

			//바닥
			color = (texture[3][texWidth * floorTex.y + floorTex.x] >> 1) &8355711;
			buffer[4*(y*width+x) +2] = color%256;
			color >>=8;
			buffer[4*(y*width+x) +1] = color%256;
			color >>=8;
			buffer[4*(y*width+x) +0] = color%256;
			buffer[4*(y*width+x) +3] = 255;
		  
			//천장
			color = texture[6][texWidth * floorTex.y + floorTex.x];
			buffer[4*((height-y)*width+x) +2] = color%256;
			color >>= 8;
			buffer[4*((height-y)*width+x) +1] = color%256;
			color >>= 8;
			buffer[4*((height-y)*width+x) +0] = color%256;
			buffer[4*((height-y)*width+x) +3] = 255;
		}
	}
	//플로어캐스팅 끝났습니다!
	//스프라이트 캐스팅 시작!
	
	for(int i=0;i<pEnemy->size();i++){
		spriteOrder[i] = i;
		spriteDistance[i] = ((pos.x - pEnemy->at(i)->getPosition().x) * (pos.x - pEnemy->at(i)->getPosition().x) + (pos.y - pEnemy->at(i)->getPosition().y) * (pos.y - pEnemy->at(i)->getPosition().y));
	}
	combSort(spriteOrder, spriteDistance, pEnemy->size());
	
	//정렬이 끝났고, 이제 존나 그릴거다.
	for(int i=0; i<pEnemy->size();i++){
		sf::Vector2f spritePos;
		spritePos.x = (float)pEnemy->at(spriteOrder[i])->getPosition().x - (float)pos.x;
		spritePos.y = (float)pEnemy->at(spriteOrder[i])->getPosition().y - (float)pos.y;

		double invDet = 1.0 / (plane.x * dir.y - dir.x * plane.y);
		sf::Vector2f transform;
		transform.x = (float)invDet * (float)(dir.y * spritePos.x - dir.x * spritePos.y);
		transform.y = (float)invDet * (float)(-plane.y * spritePos.x + plane.x * spritePos.y);
		
		int spriteScreenX = (int)((width/2) * (1+transform.x / transform.y));

		int spriteHeight = abs((int)(height/transform.y)); //이 값이 비정상적으로커지는게 문제 (transform.y 가 너무 작음)
		//printf("%f * %f + %f * %f\n", -plane.y, spritePos.x, plane.x, spritePos.y);
		sf::Vector2i renderStart;
		sf::Vector2i renderEnd;
		
		renderStart.y = -spriteHeight/2 + height/2;
		if(renderStart.y < 0) renderStart.y = 0;
		renderEnd.y = spriteHeight/2 + height/2;
		if(renderEnd.y >= height) renderEnd.y = height - 1;

		//너비계산
		int spriteWidth = abs((int)(height/transform.y));
		renderStart.x = -spriteWidth / 2 + spriteScreenX;
		if(renderStart.x < 0) renderStart.x = 0;
		renderEnd.x = spriteWidth/2 + spriteScreenX;
		if(renderEnd.x >= width) renderEnd.x = width - 1;

		for(int stripe = renderStart.x; stripe < renderEnd.x; stripe++){
			sf::Vector2i tex;
			tex.x = (int)((256 * (stripe - (-spriteWidth / 2  + spriteScreenX)) * texWidth / spriteWidth) / 256);

			if(transform.y > 0 && stripe > 0 && stripe < width && transform.y < ZBuffer[stripe]){
			
				for(int y = renderStart.y; y < renderEnd.y; y++){
					int d = y * 256 - height * 128 + spriteHeight * 128;
					tex.y = ((d*texHeight)/spriteHeight)/256;
					color = pEnemy->at(spriteOrder[i])->getConvertedTexture()->at(texWidth*tex.y+tex.x);


					//if((color & 0x00FFFFFF) != 0){
						buffer[y*width*4 + stripe*4 + 2] = color%256;
						color >>=8;
						buffer[y*width*4 + stripe*4 + 1] = color%256;
						color >>=8;
						buffer[y*width*4 + stripe*4 + 0] = color%256;
						buffer[y*width*4 + stripe*4 + 3] = 255;  
					//}
				}
			}
		}
	}
	
	


	//sprite casting 끝 ();

	drawingBuffer.create(width,height,buffer);
	drawingTex.loadFromImage(drawingBuffer);

	//sight.setParameter("colorize", colorizeRGBA[0], colorizeRGBA[1], colorizeRGBA[2], colorizeRGBA[3]);

	drawingSprite.setTexture(drawingTex);

	



	window.draw(drawingSprite, &sight);

	drawingBuffer.create(width,height,sf::Color::Black);

	for(int i=0; i<sizeof(buffer); i++){
		buffer[i] = 0;
	}
	//미니
	rec.setSize(sf::Vector2f(5,5));
	for(int i=0;i<MapY;i++){
		for(int j=0;j<MapX;j++){
			rec.setPosition(20+((MapX-j-1)*5),215+(i*5));
			if(worldMap[j][i] == 0){
				rec.setFillColor(sf::Color::White);		
			}else if(worldMap[j][i] == 1){
				rec.setFillColor(sf::Color::Black);
			}else if(worldMap[j][i] == 9){
				rec.setFillColor(sf::Color::Blue);
			}
			window.draw(rec);
			if(i > 0 && i < MapY-1 && j > 0 && j < MapX-1){//테두리는 예외처리
				if(fog[i][j] == 1){
					rec.setFillColor(sf::Color::Color(40,40,40,255));
					window.draw(rec);
				}else if(abs(j-int(pos.x)) > fov || abs(i-int(pos.y)) > fov){
					rec.setFillColor(sf::Color::Color(220,220,220,100));
					window.draw(rec);
				}
			}
		}
	}
	rec.setFillColor(sf::Color::Red);
	for(int i=0;i<pEnemy->size();i++){
		if(abs(pEnemy->at(i)->getPosition().x-pos.x) >= fov+1 || abs(pEnemy->at(i)->getPosition().y-pos.y) >= fov+1)
			continue;
		rec.setPosition(20+((MapX-int(pEnemy->at(i)->getPosition().x)-1)*5),215+(int(pEnemy->at(i)->getPosition().y)*5));
		window.draw(rec);
	}
	rec.setPosition(20+((MapX-int(pos.x)-1)*5),215+(int(pos.y)*5));
	rec.setFillColor(sf::Color::Green);
	window.draw(rec);
	//---미니맵 끝--//
}
int RayCastingScene::getAngle(){
    if(dir.x == -1 && dir.y == 0 && plane.x == 0 && plane.y == 0.66)
            return 1;
    else if(dir.x == 0 && dir.y == 1 && plane.x == 0.66 && plane.y == 0)
            return 2;
    else if(dir.x == 1 && dir.y == 0 && plane.x == 0 && plane.y == -0.66)
            return 3;
    else if(dir.x == 0 && dir.y == -1 && plane.x == -0.66 && plane.y == 0)
            return 4;
		return -1;
}
int RayCastingScene::isBattle(){
	int angle=getAngle();

	if(isGoB || isGoF || isGoL || isGoR)
		return -1;

	//printf("%d %d -- %d %d << %d\n",(int)pos.x, (int)pEnemy->at(0)->getPosition().x,(int)pos.y, (int)pEnemy->at(0)->getPosition().y,angle);

	for(int i=0; i<pEnemy->size(); i++){
		//printf("%d %d -- %d %d << %d\n",(int)pos.x, (int)pEnemy->at(i)->getPosition().x,(int)pos.y, (int)pEnemy->at(i)->getPosition().y,angle);
		if((int)pos.x == (int)pEnemy->at(i)->getPosition().x && (int)pos.y-(int)pEnemy->at(i)->getPosition().y == 1 && angle == 4){
			return i;
		}else if((int)pos.x-(int)pEnemy->at(i)->getPosition().x == -1 && (int)pos.y == (int)pEnemy->at(i)->getPosition().y && angle == 3){
			return i;
		}else if((int)pos.x == (int)pEnemy->at(i)->getPosition().x && (int)pos.y - (int)pEnemy->at(i)->getPosition().y == -1 && angle == 2){
			return i;
		}else if((int)pos.x - (int)pEnemy->at(i)->getPosition().x == 1 && (int)pos.y == (int)pEnemy->at(i)->getPosition().y && angle == 1){
			return i;
		}
	}

	//pEnemy->at(0)->getPosition().x;



	return -1;
}
int RayCastingScene::getFOV(){
	return fov;
}
void RayCastingScene::setFOV(int _fov){
	fov=_fov;
}

void RayCastingScene::setEnemies(std::vector <Enemy*> *pEnemy){
	this->pEnemy = pEnemy;
}

void RayCastingScene::setPos(sf::Vector2f temp){
	pos.x=temp.x;
	pos.y=temp.y;

	dir.x = 0; 
	dir.y = -1;
	plane.x = -0.66; 
	plane.y = 0;
	//방향값도 앞쪽을 보게 초기화해줌...
}
bool RayCastingScene::isMapChange(){
	if(/*pos.x == 2.5 && pos.y == 2.5 && */pEnemy->size() == 0)//임시조건
		return true;
	return false;
}

void RayCastingScene::setPortal(sf::Vector2i _portal){
	portal=_portal;
}