#pragma once
#include "gamecell.hpp"
#include "global.hpp"

class Map
{
public:

	GameCell layout[8][8];

	Map();

	void convertMap(char map[8][8]);

	void drawMap(sf::RenderWindow& window);


private:


};