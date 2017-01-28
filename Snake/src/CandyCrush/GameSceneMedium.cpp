
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
#define CELLS 20
#define SPEED 125
#define SNAKEX_START 10
#define SNAKEY_START 10
#define WALLS 12

GameSceneMedium::GameSceneMedium(void) : m_GridSnake{ CELL_WIDTH,CELL_HEIGHT,CELLS } {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	std::srand(std::time(0));
	timer = 0;
	snakeStartx = SNAKEX_START;
	snakeStarty = SNAKEY_START;
	appleX = rand() % (CELLS - 1) + 1;
	appleY = rand() % (CELLS - 1) + 1;
	direction = 3;
	snakeSpeed = SPEED;
	apples = 0;
	level = 1;


}

GameSceneMedium::~GameSceneMedium(void) {

}

void GameSceneMedium::OnEntry(void) {
	m_score = 0;
	lifes = 3;
	apples = 0;
	level = 1;

	snakeSpeed = SPEED;
	//m_GridSnake.generateWalls(WALLS);

}

void GameSceneMedium::OnExit(void) {
}

void GameSceneMedium::Update(void) {
	switch (apples) {
	case 5:
		level = 2;
		snakeCounter -= 5;
		break;
	case 10:
		level = 3;
		snakeCounter -= 5;
		break;
	case 25:
		SM.SetCurScene<GameSceneWin>();
		break;
	}

	if (snakeSpeed <= 30) {
		snakeSpeed = 30;
	}

	if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && direction != 1) { direction = 0; }
	if (IM.IsKeyDown<KEY_BUTTON_UP>() && direction != 0) { direction = 1; }
	if (IM.IsKeyDown<KEY_BUTTON_LEFT>() && direction != 3) { direction = 2; }
	if (IM.IsKeyDown<KEY_BUTTON_RIGHT>() && direction != 2) { direction = 3; }
	if (snakeSpeed <= 20) {
		snakeSpeed = 35;
	}
	switch (lifes) {

	case 3:
		break;
	case 2:
		break;
	case 1:
		break;
	case 0:
		SM.SetCurScene<GameSceneDeath>();
		break;
	}
	if (timer >= snakeSpeed) {
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
		timer -= snakeSpeed;
	}
	else { timer += TM.GetDeltaTime(); }

	m_GridSnake.SnakeSprite(snakeStartx, snakeStarty);
	m_GridSnake.AppleSprite(appleX, appleY);

	if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[snakeStartx][snakeStarty].objectID) {
		m_GridSnake.grid[appleX][appleY].objectID = ObjectID::SNAKE;
		appleX = rand() % (CELLS - 1) + 1; appleY = rand() % (CELLS - 1) + 1;
		snakeCounter += 1;
		m_score += 100;
		snakeSpeed -= 3;
		apples += 1;
	}

	for (int k = 0; k < CELLS; k++) {
		m_GridSnake.grid[0][k].objectID = ObjectID::WALL;
		m_GridSnake.grid[k][0].objectID = ObjectID::WALL;
		m_GridSnake.grid[CELLS - 1][k].objectID = ObjectID::WALL;
		m_GridSnake.grid[k][CELLS - 1].objectID = ObjectID::WALL;

		if (m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[0][k].objectID) {
			snakeStartx = SNAKEX_START; snakeStarty = SNAKEY_START; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
			appleX = rand() % (CELLS - 1) + 1; appleY = rand() % (CELLS - 1) + 1;
			lifes -= 1;
		}
		if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[0][k].objectID) {
			appleX = rand() % (CELLS - 1) + 1; appleY = rand() % (CELLS - 1) + 1;
		};
	}
}


void GameSceneMedium::Draw(void) {

	m_background.Draw();
	m_GridSnake.Draw(CELLS);


	GUI::DrawTextBlended<FontID::ARIAL>("LEVEL: " + std::to_string(level) + "   SCORE: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.05f), 1, 1 },
	{ 0, 0, 0 });

}
