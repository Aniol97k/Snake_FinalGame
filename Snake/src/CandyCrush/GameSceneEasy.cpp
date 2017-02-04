
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "XMLFile.h"
using namespace Logger;

#define CELL_WIDTH 25
#define CELL_HEIGHT 25
#define CELLS 25
#define APPLES 50

//EVERY PIECE OF CODE ON THIS SCENE IS THE SAME ON THE OTHER ONES, EXEPT THE XML VALUES CHANGE FOR THE LEVEL DIFFICULTY, THAT'S WHY THE OTHERS AREN'T COMMENTED

GameSceneEasy::GameSceneEasy(void): m_GridSnake{CELL_WIDTH,CELL_HEIGHT,CELLS }{
	
	//Reading the XML file to get variable values.
	ReadXML(&cells, &speed, &snakeX, &snakeY, &timerXML);

	//Image loads
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	m_HearthFull1 = { { -175,-100,W.GetWidth() / 2 ,W.GetHeight()/2 }, ObjectID::FULL_HEARTH };
	m_HearthFull2 = { { -175,20,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	m_HearthFull3 = { { -175,140,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::FULL_HEARTH };
	hearthEmpty2 = { { -175,20,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::EMPTY_HEARTH };
	hearthEmpty3 = { { -175,140,W.GetWidth() / 2 ,W.GetHeight() / 2 }, ObjectID::EMPTY_HEARTH };
	
	//Variable values settings
	std::srand(std::time(0));
	timer = 0;
	snakeStartx = snakeX;
	snakeStarty = snakeY;
	appleX = rand() % (cells - 2) + 1;
	appleY = rand() % (cells - 2) + 1;
	direction = 3;
	snakeSpeed = speed;
	apples = 0;
	level = 1;
	snakeCounter = 0;
	lastX = snakeX;
	lastY = snakeY;
	Xpos[0] = snakeStartx;
	Ypos[0] = snakeStarty;
	keyPressed = false;
	timerBarAux = 0;
	barLenght = 100;
	toAdd = 5;
	SM.score = 0;
}

GameSceneEasy::~GameSceneEasy(void) {

}

void GameSceneEasy::OnEntry(void) {

	//For each time the player re-enters the scene
	m_score = 0;
	lifes = 3;
	apples = 0;
	level = 1;
	direction = 3;
	snakeSpeed = speed;
	snakeCounter = 0;
	keyPressed = false;
	timerBarAux = 0;
	barLenght = 100;
	toAdd = 5;
	SM.score = 0;
}

void GameSceneEasy::OnExit(void) {
}

void GameSceneEasy::Update(void) {

	//Apples if that determines the level.
	if (apples == (5 + toAdd) * 1) { level = 2; toAdd++; }
	if (apples == (5 + toAdd) * 2) { level = 3; toAdd++; }
	if (apples == (5 + toAdd) * 3) { SM.SetCurScene<GameSceneDeath>(); }

	//Not needed, but in case the snake speed decreases too much: can't get negative values and sets a minimum one.
	if (snakeSpeed <= 30) {
		snakeSpeed = 30;
	}

	//For that prints with the background of the grid every value that's not a snake, apple or wall.
	for (int i = 1; i < cells - 1; i++) {
		for (int j = 1; j < cells - 1; j++) {
			if (m_GridSnake.grid[i][j].objectID == ObjectID::SNAKE || m_GridSnake.grid[i][j].objectID == ObjectID::SNAKE_HEAD) {
				m_GridSnake.grid[i][j].objectID = ObjectID::BG_CELL;
			}
		}
	}

	//If's for the players feedback, getting the direction of the snake (all possible ways: the snake can't go in the opposite direction it's going) and setting the players respone bool as true.
	if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && direction != 1) { direction = 0; keyPressed = true; }
	if (IM.IsKeyDown<KEY_BUTTON_UP>() && direction != 0) {  direction = 1; keyPressed = true;}
	if (IM.IsKeyDown<KEY_BUTTON_LEFT>() && direction != 3) { direction = 2; keyPressed = true;}
	if (IM.IsKeyDown<KEY_BUTTON_RIGHT>() && direction != 2) { direction = 3; keyPressed = true;}
	if (snakeSpeed <= 20) {
		snakeSpeed = 35;
	}

	//In case the player dies (lifes == 0), the game loads the death scene.
	if (lifes <= 0) {
		SM.SetCurScene<GameSceneDeath>();
	}
	
	//In case the player pressed a keym start the snake  movement (applies for both entering for the first time aswell for dying in the game scene)
	if (keyPressed == true) {
		//If that prints the snake alongside the timer value (timer == speed the snake goes and prints itself)
		if (timer >= snakeSpeed) {
			//Setting the values of the positions array for the snake enlargment, each one gets the position of the one ahead.
			lastX = Xpos[0];
			lastY = Ypos[0];
			Xpos[0] = snakeStartx;
			Ypos[0] = snakeStarty;

			for (int i = 0; i < APPLES; i++) {
				//Keeps setting the values of the positions array, it depends on the snake enlargment, that goes alongside the apples the snake is going to eat.
				lastX2 = Xpos[i];
				lastY2 = Ypos[i];
				Xpos[i] = lastX;
				Ypos[i] = lastY;
				lastX = lastX2;
				lastY = lastY2;
			}
			//Switch for the snake direction
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
	
	if (SM.score <= 0) { SM.score = 0; } //Just so score doesn't get negative
	
	//Printing the snake head, doesn't need to pass into a for or if because it's gonna get printed always, the position will always change.
	m_GridSnake.SnakeSpriteHead(snakeStartx, snakeStarty);

	//For that determines the snake length, depending of the snakecounter (or the apples the snake got).
	for (int i = 1; i < snakeCounter + 1; i++) {
		m_GridSnake.SnakeSprite(Xpos[i], Ypos[i]);
	}

	//If it worked 100% correctly we would apply this to generate the amount of walls we want.
		// m_GridSnake.generateWalls(AMOUNT OF WALLS WE WANT TO GENERATE)

	//Printing the apple, always gonna get printed, but the positions will change.
	m_GridSnake.AppleSprite(appleX, appleY);

	//If for when the snake eats an apple, sets variables and the apple gets printed in another position
	if (m_GridSnake.grid[appleX][appleY].objectID == m_GridSnake.grid[snakeStartx][snakeStarty].objectID) { 
		m_GridSnake.grid[appleX][appleY].objectID = ObjectID::SNAKE_HEAD;
			appleX = rand() % (cells - 2) + 1; appleY = rand() % (cells - 2) + 1;
				snakeCounter += 1; 
				snakeSpeed -= 3;
				apples += 1;
				SM.score += apples * 100;
				barLenght = 100;
							
	}

	//If tha controls that no apple is printed where the snake or snake head is
	if (m_GridSnake.grid[appleX][appleY].objectID == ObjectID::SNAKE) {
		appleX = rand() % (cells - 2) + 1; appleY = rand() % (cells - 2) + 1;
		}

	//If for the snake collision with itself or it's body.
	if (m_GridSnake.grid[snakeStartx][snakeStarty].objectID == ObjectID::SNAKE) {
		snakeStartx = snakeX; snakeStarty = snakeY; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
		appleX = rand() % (cells - 2) + 1; appleY = rand() % (cells - 2) + 1;
		lifes -= 1;
		if (SM.score >= 100) { SM.score -= 100; }
		//For the reset the snake body positions, so it's doesn't get mixed the old snake with the new one (dead and alive)
		for (int i = 1; i < APPLES; i++) {
			Xpos[i] = 0;
			Ypos[i] = 0;
		}
		keyPressed = false;
		direction = 3;
		
	}
	
	//For that goes to every wall position, and checking if the snake collision with one of them, in that case, the player loses a life and other variables values.
	for (int k = 0; k < cells; k++) {
		if (m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[0][k].objectID || m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[k][0].objectID ||
			m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[cells - 1][k].objectID || m_GridSnake.grid[snakeStartx][snakeStarty].objectID == m_GridSnake.grid[k][cells - 1].objectID) {
			m_GridSnake.grid[snakeStartx][snakeStarty].objectID = ObjectID::WALL;
			snakeStartx = snakeX; snakeStarty = snakeY; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
			appleX = rand() % (cells - 2) + 1; appleY = rand() % (cells - 2) + 1;
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
	
	//Print for the time bar, that'll change it's size every time depending of the time.
	timerBar = { { 200,725,W.GetWidth() / 2 + barLenght,W.GetHeight() / 2 - 350 }, ObjectID::BAR };

	//In case a key is pressed for the player, the bar will get smaller with the time, and getting set to full again if the player gets an apple or dies.
	if (keyPressed == true) {
		
		timerBarAux += TM.GetDeltaTime();
		if (timerBarAux >= timerXML) {
			barLenght -= 5;
			timerBarAux = 0;
		}
		if (barLenght <= -515) {
			
			snakeStartx = snakeX; snakeStarty = snakeY; m_GridSnake.grid[appleX][appleY].objectID = ObjectID::BG_CELL;
			appleX = rand() % (cells - 2) + 1; appleY = rand() % (cells - 2) + 1;
			lifes -= 1;
			if (m_score >= 100) { m_score -= apples * 100; }
			for (int i = 1; i < APPLES; i++) {
				Xpos[i] = 0;
				Ypos[i] = 0;
			}
			barLenght = 100;
			keyPressed = false;
			direction = 3;
			
					}
	}
	//If the player didn't click a key, the bar will always be full
	else {barLenght = 100;}
}


void GameSceneEasy::Draw(void) {

	//Image draws
	m_background.Draw(); 
	m_GridSnake.Draw(cells);
	timerBar.Draw();

	//Draws of the HP (lives)depending of how many the player has.
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

	//Text draw for the score and level
	GUI::DrawTextBlended<FontID::ARIAL>("LEVEL: " + std::to_string(level) + "   SCORE: " + std::to_string(SM.score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.05f), 1, 1 },
	{ 0, 0, 0 }); 
	
}

