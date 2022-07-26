#include "map.hpp"


Map::Map()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			layout[i][j].type = '0';
			layout[i][j].x = j * CELL_SIZE;
			layout[i][j].y = i * CELL_SIZE;
		}
	}
}

void Map::convertMap(char map[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			layout[i][j].type = map[i][j];
			layout[i][j].x = j * CELL_SIZE;
			layout[i][j].y = i * CELL_SIZE;
		}
	}
}

void Map::drawMap(sf::RenderWindow& window)
{
	//gray map background
	sf::RectangleShape mapBackground(sf::Vector2f(256.f, 256.f));
	mapBackground.setFillColor(sf::Color(125, 125, 125));
	window.draw(mapBackground);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sf::RectangleShape newCell(sf::Vector2f(layout[i][j].size - 1, layout[i][j].size - 1));

			//if BASE WALL
			if (layout[i][j].type == '#') 
			{
				newCell.setFillColor(sf::Color(100.f, 250.f, 50.f));
				newCell.setPosition(sf::Vector2f(layout[i][j].x + 1, layout[i][j].y + 1));
				window.draw(newCell);
			}
			else
			{
				newCell.setFillColor(sf::Color(0.f, 0.f, 0.f));
				newCell.setPosition(sf::Vector2f(layout[i][j].x + 1, layout[i][j].y + 1));
				window.draw(newCell);
			}
			
		}
	}
}