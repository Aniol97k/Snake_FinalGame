/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80



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
			std::exit(0);
		}
		else if (m_Image.transform.y == W.GetHeight() / 2 - 45) { SM.SetCurScene<GameSceneDiff>(); }
	}

}

void GameSceneWin::Draw(void) {
	m_background.Draw(); // Render background
	m_Image.Draw();


	//main scene texts

	GUI::DrawTextSolid<FontID::FACTORY>("-YOU WON-", { W.GetWidth() >> 1, int(W.GetHeight()*.1f),1, 1 }, { 0, 0, 0 }); // Render score that will be different when updated
	GUI::DrawTextSolid<FontID::FACTORY>("PLAY AGAIN", { W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("EXIT", { W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 }, { 0, 0, 0 });


	/*GUI::DrawTextBlended<FontID::FACTORY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated*/
}
