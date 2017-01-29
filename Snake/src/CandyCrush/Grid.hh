 /******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "Sprite.hh"
#include "InputManager.hh"


class GridSnake {
public:
	Sprite**grid;
	int cells;
public:

	GridSnake(int cellWidth, int cellHeight, int cellsOnGrid); 
	~GridSnake();
	
	void GridSnake::Draw(int cells);
	void GridSnake::AppleSprite(int appleCoorx, int appleCoory);
	void GridSnake::SnakeSprite(int snakeCoorx, int snakeCoory);
	void GridSnake::WallSprite(int wallCoorx, int wallCoory);
	void GridSnake::BGSprite(int bgX, int bgY);
	void GridSnake::AddSnake();
	void GridSnake::SnakeSpriteHead(int snakeCoorx, int snakeCoory);
	void GridSnake::generateWalls(int number);

	
};