#include "raycastingscene.h"
#include "stdio.h"

RayCastingScene::RayCastingScene(){
	FILE *in = fopen("map.txt","r");
	
	for(int i=0;i<mapHeight;i++){
		for(int j=0;j<mapWidth;j++){
			fscanf(in,"%d",&worldMap[i][j]);
		}
	}
	fclose(in);

	  height = 720;
	  width = 1280;
		
	  pos.x = 22; 
	  pos.y = 12;
	  dir.x = -1; 
	  dir.y = 0;
	  plane.x = 0; 
	  plane.y = 0.66;
  
	  time = 0;
	  oldTime = 0;

	  moveSpeed = 0.05;
	  rotSpeed = 0.03;

	  for(int i=0; i<8; i++){
		  texture[i].resize(texWidth * texHeight);
	  }

	  for(int x = 0; x < texWidth; x++){
		  for(int y = 0; y < texHeight; y++){
			  texture[0][texWidth*y + x] = sf::Color(255,x+y, x+y);
			  texture[1][texWidth*y + x] = sf::Color(x+y,255, x+y);
			  texture[2][texWidth*y + x] = sf::Color(x+y,x+y, 255);
			  texture[3][texWidth*y + x] = sf::Color(255,x+y, x+y);

			  texture[4][texWidth*y + x] = sf::Color(255,x+y, x+y);
			  texture[5][texWidth*y + x] = sf::Color(255,x+y, x+y);
			  texture[6][texWidth*y + x] = sf::Color(255,x+y, x+y);
			  texture[7][texWidth*y + x] = sf::Color(255,x+y, x+y);
		  }
	  }

}

sf::Color RayCastingScene::setRGB(sf::Color color){
	sf::Color returnColor;

	returnColor.r = color.r/2;
	returnColor.g = color.g/2;
	returnColor.b = color.b/2;

	return returnColor;
}


void RayCastingScene::verLine(int x, int y1, int y2, sf::Color color, sf::RenderWindow &window){
	sf::RectangleShape vLine;
	vLine.setPosition(x, y1);
	vLine.setSize(sf::Vector2f(1.0, y2- y1));
	vLine.setFillColor(color);
	window.draw(vLine);
}

void RayCastingScene::drawPoint(int x, int y, sf::Color color, sf::RenderWindow &window){
	sf::RectangleShape point;
	point.setPosition(x,y);
	point.setSize(sf::Vector2f(1.0,1.0));
	point.setFillColor(color);
	window.draw(point);
}

void RayCastingScene::update(sf::Event &event){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      if(worldMap[int(pos.x + dir.x * moveSpeed)][int(pos.y)] == false) pos.x += dir.x * moveSpeed;
      if(worldMap[int(pos.x)][int(pos.y + dir.y * moveSpeed)] == false) pos.y += dir.y * moveSpeed;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
      if(worldMap[int(pos.x - dir.x * moveSpeed)][int(pos.y)] == false) pos.x -= dir.x * moveSpeed;
      if(worldMap[int(pos.x)][int(pos.y - dir.y * moveSpeed)] == false) pos.y -= dir.y * moveSpeed;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      double oldDirX = dir.x;
      dir.x = dir.x * cos(-rotSpeed) - dir.y * sin(-rotSpeed);
      dir.y = oldDirX * sin(-rotSpeed) + dir.y * cos(-rotSpeed);
      double oldplaneX = plane.x;
      plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
      plane.y = oldplaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      double oldDirX = dir.x;
      dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
      dir.y = oldDirX * sin(rotSpeed) + dir.y * cos(rotSpeed);
      double oldplaneX = plane.x;
      plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
      plane.y = oldplaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
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

	  for(int y = drawStart; y<drawEnd; y++){
		  int d = y * 256 - height * 128 + lineHeight * 128;
		  int texY = ((d*texHeight)/lineHeight) / 256;

		  sf::Color color = texture[texNum][texHeight * texY + texX];

		  if(side == 1)
			  color = setRGB(color);
		  buffer[x][y] = color;


		 // drawPoint(x,y,buffer[x][y],window);

		 
		  point.setPosition(x,y);
	      point.setFillColor(color);
	      window.draw(point);
	  }
	  
	  



	  //여기까지 texture rendering 이었습니다!

      switch(worldMap[map.x][map.y]){
	    case 1:  color = sf::Color::Red;  break; 
        case 2:  color = sf::Color::Green;  break;
        case 3:  color = sf::Color::Blue;   break;
        case 4:  color = sf::Color::White;  break;
        default: color = sf::Color::Yellow; break;
      }
       
      if (side == 1) 
		  color = setRGB(color);

	  //verLine(x, drawStart, drawEnd, color, window);

	}
}