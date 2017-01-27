
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
using namespace Logger;

#define CELL_WIDTH 25
#define CELL_HEIGHT 25
#define CELLS_EASY 25



GameSceneEasy::GameSceneEasy(void): m_GridSnake{ "easy",CELL_WIDTH,CELL_HEIGHT,CELLS_EASY }{
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
	m_Wall = { { 50, 50, 25, 25 }, ObjectID::WALL };
	m_Apple = { { 100, 100, 25, 25 }, ObjectID::APPLE };
	m_Snake = { { 150, 150, 25, 25 }, ObjectID::SNAKE };
	m_cellBG = { { 200, 200, 25, 25 }, ObjectID::BG_CELL };
	snakeStartx = 3;
	snakeStarty = 4;
		
}

GameSceneEasy::~GameSceneEasy(void) {
}

void GameSceneEasy::OnEntry(void) {
}

void GameSceneEasy::OnExit(void) {
}

void GameSceneEasy::Update(void) {
	bool keybuttondown = false;
	if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) { keybuttondown = true; }
		
	m_GridSnake.SnakeSprite(snakeStartx, 3); 
	m_GridSnake.AppleSprite(3, 4);
	m_GridSnake.WallSprite(3, 5);
}

void GameSceneEasy::Draw(void) {
	m_background.Draw(); 
	m_GridSnake.Draw(CELLS_EASY);
	

	/*GUI::DrawTextBlended<FontID::FACTORY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated*/
}

