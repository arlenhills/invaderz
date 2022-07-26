#include "player.hpp"



Player::Player()
{
	playerDir = 0;
	playerDirVertical = 0;
	playerRot = 0;
	playerRotVertical = 0;
	x = PLAYER_START_X;
	y = PLAYER_START_Y;
	moveDistX = moveDistY = 0;

	if (!playerTexture.loadFromFile("Resources/Images/player.png"))
	{
		cout << "error loading player texture\n";
	}
	size = (float)playerTexture.getSize().y;
	playerSprite.setTexture(playerTexture);
	playerSprite.setOrigin(sf::Vector2f(8, 8));

}

void Player::update(Map& map, sf::RenderWindow& window)
{
	// direction based movement diagram you idiot
		//                       
		//         /|             
		// PMS -> / |              
		//       /  |   sin(angle) * PMS          
		//      O___|              
		//        cos(angle) * PMS               
		//                       
		//                       
	moveDistX = moveDistY = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
	{
		// y -= because vertical mirror coordinates in SFML
		moveDistY -= PLAYER_MOVE_SPEED * sin(toRad(playerDir));
		moveDistX += PLAYER_MOVE_SPEED * cos(toRad(playerDir));

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
	{
		//add 90 to direction to get angle 90 degree left of angle player is facing
		moveDistY -= PLAYER_MOVE_SPEED * sin(toRad(playerDir + 90));
		moveDistX += PLAYER_MOVE_SPEED * cos(toRad(playerDir + 90));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		//flipping the values returned by the equation to move backwards
		moveDistY += PLAYER_MOVE_SPEED * sin(toRad(playerDir));
		moveDistX -= PLAYER_MOVE_SPEED * cos(toRad(playerDir));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true)
	{
		//add 270 to direction to get angle 90 degree right of angle player is facing
		moveDistY -= PLAYER_MOVE_SPEED * sin(toRad(playerDir + 270));
		moveDistX += PLAYER_MOVE_SPEED * cos(toRad(playerDir + 270));
	}

	//turn player
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
	{
		playerDir += PLAYER_ROTATION_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
	{
		playerDir -= PLAYER_ROTATION_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
	{
		if (playerDirVertical + PLAYER_ROTATION_SPEED < 50.0f)
			playerDirVertical += PLAYER_ROTATION_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true)
	{
		if (playerDirVertical - PLAYER_ROTATION_SPEED > -50.0f)
			playerDirVertical -= PLAYER_ROTATION_SPEED;
	}*/

	window.setMouseCursorVisible(false);
	playerRot = FOV_H * (((float)WINDOWX / 2.f - (float)sf::Mouse::getPosition(window).x) / (float)WINDOWX); 
	playerRotVertical = FOV_V * (((float)WINDOWY / 2.f - (float)sf::Mouse::getPosition(window).y) / (float)WINDOWY);
	playerDir = limitDeg(playerDir + playerRot);
	playerDirVertical = playerDirVertical + playerRotVertical; if (playerDirVertical > 50.f) { playerDirVertical = 50.f; } if (playerDirVertical < -50.f) { playerDirVertical = -50.f; }
	sf::Mouse::setPosition(sf::Vector2i(WINDOWX / 2, WINDOWY / 2), window);

	//adding the valid step to position of player to move
	//check works by detecting if the future position fits in a cell with a wall in it
	if (checkCollision(x + moveDistX, y + moveDistY, map) == false)
	{
		x += moveDistX;
		y += moveDistY;
	}
	else if (checkCollision(x, y + moveDistY, map) == false)
	{
		y += moveDistY;
	}
	else if (checkCollision(x + moveDistX, y, map) == false)
	{
		x += moveDistX;
	}

	//cout << "x: " << x << "|y: " << y << endl;

	//-----CASTING DA RAYS-------
	for (int r = 0; r < WINDOWX; r++)
	{
		float rayDir = toRad(limitDeg(playerDir + 45 - (0.087890625f * r)));
		float rayDirX = cos(rayDir);
		float rayDirY = sin(rayDir);

		sf::Vector2f rayStart(x, y);
		sf::Vector2i currentCell((int)(x / CELL_SIZE), (int)(y / CELL_SIZE)); //the floor of our position gives cell index (mapX mapY in algorithm)
		sf::Vector2i rayStep(0,0); //what direction to step in x or y-direction (either +1 or -1)
		sf::Vector2f rayLength(0,0); //length of ray from current position to next x or y-side
		sf::Vector2f rayUnitDist(abs(1 / rayDirX), abs(1 / rayDirY)); //length of ray from one x or y-side to next x or y-side
		/*rayUnitDist.x = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
		rayUnitDist.y = (rayDirX == 0) ? 1e30 : abs(1 / rayDirY);*/

		float perpWallDist = 0.f;
		char side = '\0';

		//calculate step and initial sideDist
		if (rayDirX < 0)//		ray is towards left
		{
			rayStep.x = -1; //	since moving in -x direction, we should step into a cell to the -x direction
			rayLength.x = (rayStart.x / CELL_SIZE - double(currentCell.x)) * rayUnitDist.x;

		}
		else //					ray is towards right
		{
			rayStep.x = 1;
			rayLength.x = (double(currentCell.x + 1) - rayStart.x / CELL_SIZE) * rayUnitDist.x;

		}
		if (rayDirY > 0) //		ray is towards up (axis flipped)
		{
			rayStep.y = -1;
			rayLength.y = (rayStart.y / CELL_SIZE - double(currentCell.y)) * rayUnitDist.y;

		}
		else //					ray is towards down (axis flipped)
		{
			rayStep.y = 1;
			rayLength.y = (double(currentCell.y + 1) - rayStart.y / CELL_SIZE) * rayUnitDist.y;

		}

		bool hit = false;
		float renderDist = 0;
		while (hit == false && renderDist <= maxRenderDistance)
		{
			side = '\0';
			if (rayLength.x < rayLength.y)
			{
				renderDist = rayLength.x;
				rayLength.x		+= rayUnitDist.x;
				currentCell.x	+= rayStep.x;
				side = 'v';
			}
			else
			{
				renderDist = rayLength.y;
				rayLength.y		+= rayUnitDist.y;
				currentCell.y	+= rayStep.y;
				side = 'h';
			}
			if (currentCell.x >= 0 && currentCell.x <= 7 && currentCell.y >= 0 && currentCell.y <= 7)
			{
				if (map.layout[currentCell.y][currentCell.x].type == '#')
				{
					hit = true;
				}
			}
		}
		//collision occured
		if (hit == true)
		{
			viewRays[r].dist = renderDist;
			//cout << viewRays[r].dist << endl;
			viewRays[r].angle = rayDir;
			viewRays[r].side = side;
		}
	}
}

void Player::shoot(sf::RenderWindow& window)
{
	sf::CircleShape bullet(20.f, 12);
	bullet.setFillColor(sf::Color::Yellow);
	bullet.setPosition(WINDOWX / 2 + 158, WINDOWY - 113);
	window.draw(bullet);
}

void Player::drawMap(sf::RenderWindow& window)
{

	float frameAngle = 360.f / (playerTexture.getSize().x / size);
	//We need to shift the angles by half so that their bisector matches the frames.
	float shiftedDirection = fmod(360 + fmod(playerDir + 0.5f * frameAngle, 360), 360);
	playerSprite.setPosition(x, y);
	playerSprite.setTextureRect(sf::IntRect(16 * floor(shiftedDirection / frameAngle), 0, size, size));

	for (int r = 0; r < WINDOWX; r++)
	{
		sf::Vector2f rayPoint(x + viewRays[r].dist * cos(viewRays[r].angle), y + viewRays[r].dist * -sin(viewRays[r].angle));
		sf::Vertex ray[] =
		{
			sf::Vertex(sf::Vector2f(x,y)),
			sf::Vertex(rayPoint)
		};
		ray[0].color = sf::Color::Magenta;
		ray[1].color = sf::Color::Magenta;
		window.draw(ray,2,sf::Lines);
	}

	window.draw(playerSprite);
}

void Player::draw3D(sf::RenderWindow& window)
{
	

	for (int l = 0; l < WINDOWX; l++)
	{
		float floorOffset = round(WINDOWY/2.f * ((0.5f * tan(toRad(playerDirVertical)) / tan(toRad(0.5f * FOV_V)))));

		// WINDOWY * shrinkfactor
		int lineHeight = (int)(WINDOWY * 0.666666 / (viewRays[l].dist * cos(toRad(playerDir) - viewRays[l].angle))); //if (lineHeight > WINDOWY) lineHeight = WINDOWY;
		int drawStart = (float)((-lineHeight / 2 + WINDOWY / 2) + floorOffset); //if (drawStart < 0) drawStart = 0;
		int columnPos = round(WINDOWX * (0.5f + (0.5f * tan(toRad(playerDir) - viewRays[l].angle) / tan(toRad(0.5f * FOV_H)))));
		short nextColumnPos = WINDOWX;

		if (l < WINDOWX - 1) nextColumnPos = round(WINDOWX * (0.5f + (0.5f * tan(toRad(playerDir) - viewRays[l+1].angle) / tan(toRad(0.5f * FOV_H)))));
		sf::RectangleShape column(sf::Vector2f(std::max(1, nextColumnPos - columnPos), lineHeight));

		//texturing
		if (viewRays[l].side == 'v') { column.setFillColor(sf::Color(0, 250, 0)); }
		else if (viewRays[l].side == 'h') { column.setFillColor(sf::Color(0, 150, 0)); }

		column.setPosition(columnPos, drawStart);
		window.draw(column);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		shoot(window);
	}
}


