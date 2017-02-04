#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "Binary.h"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80


//CHECK THE COMMENTS ON "GameSceneMenu.cpp" AS IT APPLIES TO EVERY SCENE OF THIS TYPE

GameSceneWin::GameSceneWin(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_WIN };
	int arrowHeight = W.GetHeight() / 2 - 45;
	m_Image = { { W.GetWidth() / 2 - 180, arrowHeight,90,90 }, ObjectID::ARROW };
}

GameSceneWin::~GameSceneWin(void) {
}

void GameSceneWin::OnEntry(void) {
}

void GameSceneWin::OnExit(void) {
}

void GameSceneWin::Update(void) {

	if (m_Image.transform.y == W.GetHeight() / 2 - 45) {
		m_Image.transform.x = W.GetWidth() / 2 - 280;
	}
	else { m_Image.transform.x = W.GetWidth() / 2 - 180; }

	if (IM.IsKeyDown<KEY_BUTTON_UP>()) { m_Image.transform.y = W.GetHeight() / 2 - 45; }
	else if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) { m_Image.transform.y = W.GetHeight() / 2 + 30; }
	else if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
		if (m_Image.transform.y == W.GetHeight() / 2 + 30) {
			std::exit(0); //function that exits the game
		}
		else if (m_Image.transform.y == W.GetHeight() / 2 - 45) { SM.SetCurScene<GameSceneDiff>(); }
	}

}

void GameSceneWin::Draw(void) {
	m_background.Draw(); 
	m_Image.Draw();

	GUI::DrawTextSolid<FontID::FACTORY>("-YOU WON-", { W.GetWidth() >> 1, int(W.GetHeight()*.1f),1, 1 }, { 0, 0, 0 }); 
	GUI::DrawTextSolid<FontID::FACTORY>("SCORE: " + std::to_string(SM.score), { W.GetWidth() >> 1, int(W.GetHeight()*.3f),1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("PLAY AGAIN", { W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("EXIT", { W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 }, { 0, 0, 0 });


	
}
