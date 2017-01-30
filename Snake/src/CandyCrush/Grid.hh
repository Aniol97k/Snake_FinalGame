#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

//Class GridSnake implementation of the varaibles and functions

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