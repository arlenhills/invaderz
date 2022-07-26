#include "collision.hpp"

bool checkCollision(float nextX, float nextY, Map& map)
{
	bool OOB = false;
	int cellPosX = (int)floor(nextX / CELL_SIZE);
	int cellPosY = (int)floor(nextY / CELL_SIZE);
	
	if (map.layout[cellPosY][cellPosX].type == '#')
		OOB = true;

	////stop going down
	//if (nextY > map.layout[cellPosY + 1][cellPosX].y && map.layout[cellPosY + 1][cellPosX].type == '#')
	//{
	//	OOB = true;
	//}
	////stop going right
	//if (nextX > map.layout[cellPosY][cellPosX + 1].x && map.layout[cellPosY][cellPosX + 1].type == '#')
	//{
	//	OOB = true;
	//}
	////stop going up
	//if (nextY < map.layout[cellPosY - 1][cellPosX].y + 32 && map.layout[cellPosY - 1][cellPosX].type == '#')
	//{
	//	OOB = true;
	//}
	////stop going left
	//if (nextX < map.layout[cellPosY][cellPosX - 1].x + 32 && map.layout[cellPosY][cellPosX - 1].type == '#')
	//{
	//	OOB = true;
	//}

	return OOB;
}
