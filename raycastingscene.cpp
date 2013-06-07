#include "raycastingscene.h"
#include <stdio.h>
#include <math.h>

RayCastingScene::RayCastingScene(){
	FILE *in = fopen("map.txt","r");
	
	for(int i=0;i<mapHeight;i++){
		for(int j=0;j<mapWidth;j++){
			fscanf(in,"%d",&worldMap[i][j]);
		}
	}
	fclose(in);

	  height = 360;
	  width = 640;
		
	  pos.x = 1.5; 
	  pos.y = 1.5;
	  dir.x = -1; 
	  dir.y = 0;
	  plane.x = 0; 
	  plane.y = 0.66;

	  //---이동---//
	  //player.x = 1.5;
	  //player.y = 1.5;
	  isTurnL=0;
	  isTurnR=0;
	  isGoF=0;
	  isGoR=0;

	  pressS=false;
	  pressW=false;
	  pressA=false;
	  pressD=false;
	  //---
  
	  time = 0;
	  oldTime = 0;

	  moveSpeed = 0.05;
	  rotSpeed = 0.07875;

	  for(int i=0; i<8; i++){
		  realTexture[i].resize(texWidth * texHeight);
	  }

	  for(int x = 0; x < texWidth; x++){
		  for(int y = 0; y < texHeight; y++){

			  realTexture[0][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);
			  realTexture[1][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);
			  realTexture[2][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);
			  realTexture[3][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);

			  realTexture[4][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);
			  realTexture[5][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);
			  realTexture[6][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);
			  realTexture[7][texWidth*y + x] = 65536 * 192 * (x % 16 && y % 16);
		  }
	  }

	  drawingBuffer.create(width,height,sf::Color::Black);

}


void RayCastingScene::update(sf::Event &event){
	if (isGoF == 0 && isGoR == 0 && isTurnL == 0 && isTurnR == 0){//현재 멈춰있는 상태(노 애니메이션)		
		if(pressW == false && worldMap[int(pos.x+dir.x)][int(pos.y+dir.y)] == false &&  sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			pressW=true;
			isGoF=20;
		}
		if(pressS == false && worldMap[int(pos.x-dir.x)][int(pos.y-dir.y)] == false &&  sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			pressS=true;
			isGoR=20;
		}
		if(pressA == false && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			pressA=true;
			isTurnL=20;
		}
		if(pressD == false && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			pressD=true;
			isTurnR=20;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) == false)
		pressW=false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) == false)
		pressS=false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) == false)
		pressA=false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) == false)
		pressD=false;

	if(isTurnR != 0){
		isTurnR--;
		//---
		double oldDirX = dir.x;
		dir.x = dir.x * cos(-rotSpeed) - dir.y * sin(-rotSpeed);
		dir.y = oldDirX * sin(-rotSpeed) + dir.y * cos(-rotSpeed);
		double oldplaneX = plane.x;
		plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
		plane.y = oldplaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);
	}else if(isTurnL != 0){
		isTurnL--;
		//---
		double oldDirX = dir.x;
		dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
		dir.y = oldDirX * sin(rotSpeed) + dir.y * cos(rotSpeed);
		double oldplaneX = plane.x;
		plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
		plane.y = oldplaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
	}else if(isGoF != 0){
		isGoF--;
		pos.x += floor(dir.x+0.5) * moveSpeed;
		pos.y += floor(dir.y+0.5) * moveSpeed;
		if(isGoF == 0){
			pos.x=(int)pos.x+0.5;
			pos.y=(int)pos.y+0.5;
		}
	}else if(isGoR != 0){
		isGoR--;
		pos.x -= floor(dir.x+0.5) * moveSpeed;
		pos.y -= floor(dir.y+0.5) * moveSpeed;
		if(isGoR == 0){
			pos.x=(int)pos.x+0.5;
			pos.y=(int)pos.y+0.5;
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
	  //특히 realBuffer 에 값을 대입할때
	  for(int y = drawStart; y<drawEnd; y++){
		  
		  int d = y * 256 - height * 128 + lineHeight * 128;
		  int texY = ((d*texHeight)/lineHeight) / 256;
		  
		  color = realTexture[texNum][texHeight * texY + texX];
		  
		  if(side == 1)
			  color = (color >> 1) & 8355711;
			 
		  realBuffer[y*width*4 + x*4 + 2] = color%256;
		  color >>=8;
		  realBuffer[y*width*4 + x*4 + 1] = color%256;
		  color >>=8;
		  realBuffer[y*width*4 + x*4 + 0] = color%256;
		  realBuffer[y*width*4 + x*4 + 3] = 255;  
	  }
	  
	  



	  //여기까지 texture rendering 이었습니다!

      
	}

	drawingBuffer.create(width,height,realBuffer);
	drawingTex.loadFromImage(drawingBuffer);
	drawingSprite.setTexture(drawingTex);

	window.draw(drawingSprite);

	drawingBuffer.create(width,height,sf::Color::Black);

	for(int i=0; i<sizeof(realBuffer); i++){
		realBuffer[i] = 0;
	}

}