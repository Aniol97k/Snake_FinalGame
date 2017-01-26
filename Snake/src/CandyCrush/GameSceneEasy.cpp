
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80



GameSceneEasy::GameSceneEasy(void){
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_GAME };
		
}

GameSceneEasy::~GameSceneEasy(void) {
}

void GameSceneEasy::OnEntry(void) {
}

void GameSceneEasy::OnExit(void) {
}

void GameSceneEasy::Update(void) {
}

void GameSceneEasy::Draw(void) {
	m_background.Draw(); 
	

	/*GUI::DrawTextBlended<FontID::FACTORY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated*/
}

