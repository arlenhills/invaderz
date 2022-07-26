#pragma once
#include "global.hpp"


class GameCell
{
public:

	float size;
	float x;
	float y;
	char type;

	GameCell()
	{
		size = CELL_SIZE;
		x = 0.f;
		y = 0.f;
		type = '0';
	};

private:

};