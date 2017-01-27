
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



GameSceneEasy::GameSceneEasy(void): m_GridSnake{CELL_WIDTH,CELL_HEIGHT,CELLS_EASY }{
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	m_Wall = { { 50, 50, 25, 25 }, ObjectID::WALL };
	m_Apple = { { 100, 100, 25, 25 }, ObjectID::APPLE };
	m_Snake = { { 150, 150, 25, 25 }, ObjectID::SNAKE };
	m_cellBG = { { 200, 200, 25, 25 }, ObjectID::BG_CELL };
	std::srand(std::time(0));
	timer = 0;
	snakeStartx = 12;
	snakeStarty = 12;
	appleX = rand() % 24 + 1;
	appleY = rand() % 24 + 1;
	m_score = 0;
	direction = 2;
	moveleft = false;
}

GameSceneEasy::~GameSceneEasy(void) {
}

void GameSceneEasy::OnEntry(void) {
}

void GameSceneEasy::OnExit(void) {
}

void GameSceneEasy::Update(void) {
	if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) {  direction = 0; }
	if (IM.IsKeyDown<KEY_BUTTON_UP>()) { m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStartx -= 1; movedown = true; }
	if (IM.IsKeyDown<KEY_BUTTON_LEFT>()) { m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStarty -= 1; moveleft = false; }
	if (IM.IsKeyDown<KEY_BUTTON_RIGHT>()) { m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStarty += 1; moveleft = true; }

	if (timer >= 0.25) {
		switch (direction) {
		case 0:
			m_GridSnake.BGSprite(snakeStartx, snakeStarty); snakeStartx += 1;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
			
		}
		timer -= 0.25;
	}
	else { timer += TM.GetDeltaTime(); }
	m_GridSnake.SnakeSprite(snakeStartx, snakeStarty);
	m_GridSnake.AppleSprite(appleX, appleY);
	m_GridSnake.WallSprite(3, 5);
	if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[snakeStartx][snakeStarty].objectID) { m_GridSnake.grid[appleX][appleY].objectID = ObjectID::SNAKE; appleX = rand() % 24 + 1; appleY = rand() % 24 + 1; snakeCounter += 1; }
	// //if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[snakeStartx][snakeStarty].objectID) { m_GridSnake.grid[appleX][appleY].objectID = ObjectID::SNAKE; appleX = rand() % 24 + 1; appleY = rand() % 24 + 1; snakeCounter += 1; }
}


void GameSceneEasy::Draw(void) {
	m_background.Draw(); 
	m_GridSnake.Draw(CELLS_EASY);
	

	/*GUI::DrawTextBlended<FontID::FACTORY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated*/
}

