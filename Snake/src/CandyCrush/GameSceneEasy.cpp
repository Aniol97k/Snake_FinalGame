
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace Logger;

#define CELL_WIDTH 25
#define CELL_HEIGHT 25
#define CELLS_EASY 25
#define SPEED_EASY 200
#define SNAKEX_START 12
#define SNAKEY_START 12

GameSceneEasy::GameSceneEasy(void): m_GridSnake{CELL_WIDTH,CELL_HEIGHT,CELLS_EASY }{
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	m_Wall = { { 50, 50, 25, 25 }, ObjectID::WALL };
	m_Apple = { { 100, 100, 25, 25 }, ObjectID::APPLE };
	m_Snake = { { 150, 150, 25, 25 }, ObjectID::SNAKE };
	m_cellBG = { { 200, 200, 25, 25 }, ObjectID::BG_CELL };
	std::srand(std::time(0));
	timer = 0;
	snakeStartx = SNAKEX_START;
	snakeStarty = SNAKEY_START;
	appleX = rand() % 24 + 1;
	appleY = rand() % 24 + 1;
	m_score = 0;
	direction = 3;
	lifes = 3;
	
	
}

GameSceneEasy::~GameSceneEasy(void) {
}

void GameSceneEasy::OnEntry(void) {
}

void GameSceneEasy::OnExit(void) {
}

void GameSceneEasy::Update(void) {
	if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && direction !=1) {  direction = 0; }
	if (IM.IsKeyDown<KEY_BUTTON_UP>() && direction != 0) {  direction = 1; }
	if (IM.IsKeyDown<KEY_BUTTON_LEFT>() && direction != 3) { direction = 2; }
	if (IM.IsKeyDown<KEY_BUTTON_RIGHT>() && direction != 2) { direction = 3; }
	
	switch (lifes) {

	case 3:
		break;
	case 2:
		break;
	case 1:
		break;
	case 0:
		//Dead Scene // SM.SetCurScene<GameSceneMenu>();
		break;
	}
	if (timer >= SPEED_EASY) {
		switch (direction) {
		case 0:
			m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStartx += 1;
			break;
		case 1:
			m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStartx -= 1;
			break;
		case 2:
			m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStarty -= 1;
			break;
		case 3:
			m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStarty += 1;
			break;
			
		}
		timer -= SPEED_EASY;
	}
	else { timer += TM.GetDeltaTime(); }
	m_GridSnake.SnakeSprite(snakeStartx, snakeStarty);
	m_GridSnake.AppleSprite(appleX, appleY);
	m_GridSnake.WallSprite(3, 5);
	if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[snakeStartx][snakeStarty].objectID) { m_GridSnake.grid[appleX][appleY].objectID = ObjectID::SNAKE; appleX = rand() % 24 + 1; appleY = rand() % 24 + 1; snakeCounter += 1; m_score += 100; }
	

	for (int k = 0; k < CELLS_EASY; k++) {
		m_GridSnake.grid[0][k].objectID = ObjectID::WALL;
		m_GridSnake.grid[k][0].objectID = ObjectID::WALL;
		m_GridSnake.grid[CELLS_EASY - 1][k].objectID = ObjectID::WALL;
		m_GridSnake.grid[k][CELLS_EASY - 1].objectID = ObjectID::WALL;
		if (m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[0][k].objectID) { snakeStartx = SNAKEX_START; snakeStarty = SNAKEY_START; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL; appleX = rand() % 24 + 1; appleY = rand() % 24 + 1; lifes -= 1; }
		if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[0][k].objectID) { appleX = rand() % 24 + 1; appleY = rand() % 24 + 1;};
	}
}


void GameSceneEasy::Draw(void) {

	m_background.Draw(); 
	m_GridSnake.Draw(CELLS_EASY);
		

	GUI::DrawTextBlended<FontID::ARIAL>("SCORE: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.05f), 1, 1 },
	{ 0, 0, 0 }); // Render score that will be different when updated*/
}

