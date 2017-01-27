/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include <ctime>
#include "Grid.hh"
#include "Window.hh"
#include "IOManager.hh"
#include "TimeManager.hh"

GridSnake::GridSnake(int cellWidth, int cellHeight, int cellsOnGrid)
	{
		cells = cellsOnGrid;
		grid = new Sprite *[cells];
		for (int i = 0; i < cells; i++) {grid[i] = new Sprite[cells];}
		for (int i = 0; i < cells; i++) {
			for (int j = 0; j < cells; j++) {grid[i][j].transform = { j * (+26) + (((W.GetWidth() - cellWidth*cells) - 35) >> 1),
					i * (cellHeight + 1) + ((W.GetHeight() - cellHeight*cells) >> 1),
						cellWidth, cellHeight };
				grid[i][j].objectID = ObjectID::BG_CELL;	}	
		}	

		for (int k = 0; k < cells; k++) {
			grid[0][k].objectID = ObjectID::WALL;
			grid[k][0].objectID = ObjectID::WALL;
			grid[cells - 1][k].objectID = ObjectID::WALL;
			grid[k][cells - 1].objectID = ObjectID::WALL;
		}

	

	
}
GridSnake::~GridSnake() {}

void GridSnake::Draw(int cells){
	for (int i = 0; i < cells; i++) {
		for (int j = 0; j < cells; ++j) {
			grid[i][j].Draw();
		}
	}
}

void GridSnake::SnakeSprite(int snakeCoorx, int snakeCoory) {
	grid[snakeCoorx][snakeCoory].objectID = ObjectID::SNAKE;
}

void GridSnake::AppleSprite(int appleCoorx, int appleCoory) {
	grid[appleCoorx][appleCoory].objectID = ObjectID::APPLE;

}

void GridSnake::WallSprite(int wallCoorx, int wallCoory) {
	grid[wallCoorx][wallCoory].objectID = ObjectID::WALL;

}

void GridSnake::SnakeMoveX(int snakeCoorx, int snakeCoory) {
	grid[snakeCoorx][snakeCoory].objectID = ObjectID::BG_CELL;
	grid[snakeCoorx + 1][snakeCoory].objectID = ObjectID::SNAKE;
}
void GridSnake::BGSprite(int bgX, int bgY) {

	grid[bgX][bgY].objectID = ObjectID::BG_CELL;
}


