
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "XMLFile3.h"
using namespace Logger;

#define CELL_WIDTH 25
#define CELL_HEIGHT 25
#define CELLS 15


GameSceneHard::GameSceneHard(void) : m_GridSnake{ CELL_WIDTH,CELL_HEIGHT,CELLS } {
	ReadXML3(&cellsH, &speedH, &snakeXH, &snakeYH);
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	m_HearthFull1 = { { -50,0,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	m_HearthFull2 = { { -50,120,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	m_HearthFull3 = { { -50,240,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	hearthEmpty2 = { { -50,120,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::EMPTY_HEARTH };
	hearthEmpty3 = { { -50,240,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::EMPTY_HEARTH };
	std::srand(std::time(0));
	timer = 0;
	snakeStartx = snakeXH;
	snakeStarty = snakeYH;
	appleX = rand() % (cellsH - 1) + 1;
	appleY = rand() % (cellsH - 1) + 1;
	direction = 3;
	snakeSpeed = speedH;
	apples = 0;
	level = 1;


}

GameSceneHard::~GameSceneHard(void) {

}

void GameSceneHard::OnEntry(void) {
	m_score = 0;
	lifes = 3;
	apples = 0;
	level = 1;

	snakeSpeed = speedH;
	
}

void GameSceneHard::OnExit(void) {
}

void GameSceneHard::Update(void) {
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
		appleX = rand() % (cellsH - 1) + 1; appleY = rand() % (cellsH - 1) + 1;
		snakeCounter += 1;
		m_score += 100;
		snakeSpeed -= 3;
		apples += 1;
	}

	for (int k = 0; k < cellsH; k++) {
		m_GridSnake.grid[0][k].objectID = ObjectID::WALL;
		m_GridSnake.grid[k][0].objectID = ObjectID::WALL;
		m_GridSnake.grid[cellsH - 1][k].objectID = ObjectID::WALL;
		m_GridSnake.grid[k][cellsH - 1].objectID = ObjectID::WALL;

		if (m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[0][k].objectID) {
			snakeStartx = snakeXH; snakeStarty = snakeYH; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
			appleX = rand() % (cellsH - 1) + 1; appleY = rand() % (cellsH - 1) + 1;
			lifes -= 1;
		}
		if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[0][k].objectID) {
			appleX = rand() % (cellsH - 1) + 1; appleY = rand() % (cellsH - 1) + 1;
		};
	}
}


void GameSceneHard::Draw(void) {

	m_background.Draw();
	m_GridSnake.Draw(cellsH);

	switch (lifes) {

	case 3:
		m_HearthFull1.Draw();
		m_HearthFull2.Draw();
		m_HearthFull3.Draw();
		break;
	case 2:
		m_HearthFull1.Draw();
		m_HearthFull2.Draw();
		hearthEmpty3.Draw();
		break;
	case 1:
		m_HearthFull1.Draw();
		hearthEmpty2.Draw();
		hearthEmpty3.Draw();
		break;
	}


	GUI::DrawTextBlended<FontID::ARIAL>("LEVEL: " + std::to_string(level) + "   SCORE: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*0.15f), 1, 1 },
	{ 0, 0, 0 });

}
