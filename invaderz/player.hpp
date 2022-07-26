#pragma once
#include "global.hpp"
#include "map.hpp"
#include "radian.hpp"
#include "degrees.hpp"
#include "collision.hpp"

typedef struct ray
{
	double dist;
	double angle;
	char side;
}Ray;

class Player : public sf::RectangleShape {
public:
	Player();

	float playerDir, playerDirVertical;
	float playerRot, playerRotVertical;
	float x, moveDistX;
	float y, moveDistY;
	float size;

	//dist - ray length
	//angle - ray angle in radians
	//side - v or h hit
	Ray viewRays[WINDOWX];

	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	void update(Map& map, sf::RenderWindow& window);
	void shoot(sf::RenderWindow& window);
	void drawMap(sf::RenderWindow& window);
	void draw3D(sf::RenderWindow& window);
	
private:

};