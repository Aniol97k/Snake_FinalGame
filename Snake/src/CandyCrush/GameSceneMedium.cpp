
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "XMLFile2.h"
using namespace Logger;

#define CELL_WIDTH 25
#define CELL_HEIGHT 25
#define CELLS 20
#define APPLES 25

//READ FIRST COMMENT ON "GameSceneEasy.cpp"

GameSceneMedium::GameSceneMedium(void) : m_GridSnake{ CELL_WIDTH,CELL_HEIGHT,CELLS } {
	ReadXML2(&cellsM, &speedM, &snakeXM, &snakeYM, &timerXMLM);
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	m_HearthFull1 = { { -150,-50,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	m_HearthFull2 = { { -150,70,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	m_HearthFull3 = { { -150,190,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	hearthEmpty2 = { { -150,70,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::EMPTY_HEARTH };
	hearthEmpty3 = { { -150,190,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::EMPTY_HEARTH };

	std::srand(std::time(0));
	timer = 0;
	snakeStartx = snakeXM;
	snakeStarty = snakeYM;
	appleX = rand() % (cellsM - 2) + 1;
	appleY = rand() % (cellsM- 2) + 1;
	direction = 3;
	snakeSpeed = speedM;
	apples = 0;
	level = 1;
	snakeCounter = 0;
	lastX = snakeXM;
	lastY = snakeYM;
	Xpos[0] = snakeStartx;
	Ypos[0] = snakeStarty;
	keyPressed = false;
	timerBarMAux = 0;
	barLenght = 100;
	toAdd = 5;
	SM.score = 0;

}

GameSceneMedium::~GameSceneMedium(void) {

}

void GameSceneMedium::OnEntry(void) {
	m_score = 0;
	lifes = 3;
	apples = 0;
	level = 1;
	direction = 3;
	snakeSpeed = speedM;
	snakeCounter = 0;
	keyPressed = false;
	timerBarMAux = 0;
	barLenght = 100;
	toAdd = 5;
	SM.score = 0;

}

void GameSceneMedium::OnExit(void) {
}

void GameSceneMedium::Update(void){
	//Apples if that determines the level.
	if (apples == (5 + toAdd) * 1) { level = 2; toAdd += 2; }
	if (apples == (5 + toAdd) * 2) { level = 3; toAdd+=2; }
	if (apples == (5 + toAdd) * 3) { SM.SetCurScene<GameSceneDeath>(); }

		if (snakeSpeed <= 30) {
			snakeSpeed = 30;
		}
		for (int i = 1; i < cellsM - 1; i++) {
			for (int j = 1; j < cellsM - 1; j++) {
				if (m_GridSnake.grid[i][j].objectID == ObjectID::SNAKE || m_GridSnake.grid[i][j].objectID == ObjectID::SNAKE_HEAD) {
					m_GridSnake.grid[i][j].objectID = ObjectID::BG_CELL;
				}
			}
		}
		if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && direction != 1) { direction = 0; keyPressed = true; }
		if (IM.IsKeyDown<KEY_BUTTON_UP>() && direction != 0) { direction = 1; keyPressed = true;}
		if (IM.IsKeyDown<KEY_BUTTON_LEFT>() && direction != 3) { direction = 2; keyPressed = true; }
		if (IM.IsKeyDown<KEY_BUTTON_RIGHT>() && direction != 2) { direction = 3; keyPressed = true;}
		if (snakeSpeed <= 20) {
			snakeSpeed = 35;
		}

		if (lifes <= 0) {
			SM.SetCurScene<GameSceneDeath>();
		}

		if (SM.score <= 0) { SM.score = 0; }

		if (keyPressed == true) {

			if (timer >= snakeSpeed) {
				lastX = Xpos[0];
				lastY = Ypos[0];
				Xpos[0] = snakeStartx;
				Ypos[0] = snakeStarty;

				for (int i = 0; i < APPLES; i++) {
					lastX2 = Xpos[i];
					lastY2 = Ypos[i];
					Xpos[i] = lastX;
					Ypos[i] = lastY;
					lastX = lastX2;
					lastY = lastY2;
				}

				switch (direction) {
				case 0:
					snakeStartx += 1;
					break;
				case 1:
					snakeStartx -= 1;
					break;
				case 2:
					snakeStarty -= 1;
					break;
				case 3:
					snakeStarty += 1;
					break;

				}
				timer -= snakeSpeed;
			}
			else { timer += TM.GetDeltaTime(); }
		}

		m_GridSnake.SnakeSpriteHead(snakeStartx, snakeStarty);

		for (int i = 1; i < snakeCounter + 1; i++) {
			m_GridSnake.SnakeSprite(Xpos[i], Ypos[i]);
		}


		//If it worked 100% correctly we would apply this to generate the amount of walls we want.
		// m_GridSnake.generateWalls(AMOUNT OF WALLS WE WANT TO GENERATE)

		m_GridSnake.AppleSprite(appleX, appleY);

		if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[snakeStartx][snakeStarty].objectID) {
			m_GridSnake.grid[appleX][appleY].objectID = ObjectID::SNAKE_HEAD;
			appleX = rand() % (cellsM - 2) + 1; appleY = rand() % (cellsM - 2) + 1;
			snakeCounter += 1;
			snakeSpeed -= 3;
			apples += 1;
			barLenght = 100;
			SM.score += apples * 100;

		}

		if (m_GridSnake.grid[appleX][appleY].objectID == ObjectID::SNAKE) {
			appleX = rand() % (cellsM - 2) + 1; appleY = rand() % (cellsM - 2) + 1;
		}

		if (m_GridSnake.grid[snakeStartx][snakeStarty].objectID == ObjectID::SNAKE) {
			snakeStartx = snakeXM; snakeStarty = snakeYM; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
			appleX = rand() % (cellsM - 2) + 1; appleY = rand() % (cellsM - 2) + 1;
			lifes -= 1;
			if (SM.score >= 100) { SM.score -= apples * 100; }
			for (int i = 1; i < APPLES; i++) {
				Xpos[i] = 0;
				Ypos[i] = 0;
			}
			keyPressed = false;
			direction = 3;

		}


		for (int k = 0; k < cellsM; k++) {
			if (m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[0][k].objectID || m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[k][0].objectID ||
				m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[cellsM - 1][k].objectID || m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[k][cellsM - 1].objectID) {
				m_GridSnake.grid[snakeStartx][snakeStarty].objectID = ObjectID::WALL;
				snakeStartx = snakeXM; snakeStarty = snakeYM; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
				appleX = rand() % (cellsM - 2) + 1; appleY = rand() % (cellsM - 2) + 1;
				lifes -= 1;
				if (SM.score >= 100) { SM.score -= apples * 100; }
				for (int i = 1; i < APPLES; i++) {
					Xpos[i] = 0;
					Ypos[i] = 0;
				}
				keyPressed = false;
				direction = 3;

			}
		}


		timerBar = { { 200,675,W.GetWidth() / 2 + barLenght,W.GetHeight() / 2 - 350 }, ObjectID::BAR };

		if (keyPressed == true) {

			timerBarMAux += TM.GetDeltaTime();
			if (timerBarMAux >= timerXMLM) {
				barLenght -= 5;
				timerBarMAux = 0;
			}
			if (barLenght <= -515) {

				snakeStartx = snakeXM; snakeStarty = snakeYM; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
				appleX = rand() % (cellsM - 2) + 1; appleY = rand() % (cellsM - 2) + 1;
				lifes -= 1;
				if (SM.score >= 100) { SM.score -= 100; }
				for (int i = 1; i < APPLES; i++) {
					Xpos[i] = 0;
					Ypos[i] = 0;
				}
				barLenght = 100;
				keyPressed = false;
				direction = 3;

			}
		}
		else { barLenght = 100; }
}


void GameSceneMedium::Draw(void) {

	m_background.Draw();
	m_GridSnake.Draw(cellsM);
	timerBar.Draw();

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


	GUI::DrawTextBlended<FontID::ARIAL>("LEVEL: " + std::to_string(level) + "   SCORE: " + std::to_string(SM.score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 0, 0, 0 });

}
