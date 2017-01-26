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



GameScene2::GameScene2(void) : m_grid("lvl/testLvl.dat", CELL_WIDTH, CELL_HEIGHT) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	int arrowHeight = W.GetHeight() / 2 - 45;
	m_Image = { { W.GetWidth() / 2 - 180, arrowHeight,90,90 }, ObjectID::ARROW };
}

GameScene2::~GameScene2(void) {
}

void GameScene2::OnEntry(void) {
}

void GameScene2::OnExit(void) {
}

void GameScene2::Update(void) {
	
	if (m_Image.transform.y == W.GetHeight() / 2 - 45) {
		m_Image.transform.x = W.GetWidth() / 2 - 250;

	}
	else { m_Image.transform.x = W.GetWidth() / 2 - 180; }

	if (IM.IsKeyDown<KEY_BUTTON_UP>() && m_Image.transform.y != W.GetHeight() / 2 - 120) { m_Image.transform.y -= 75; }
	else if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && m_Image.transform.y != W.GetHeight() / 2 + 30) { m_Image.transform.y += 75; }
	else if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
		if (m_Image.transform.y == W.GetHeight() / 2 + 30) {
			// Enter easy game
		}
		else if (m_Image.transform.y == W.GetHeight() / 2 - 45) {
			//Enter medium game
		}
		else if (m_Image.transform.y == W.GetHeight() / 2 - 120) {
			//Enter hard game
		}
	}

	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
		m_grid.CheckMouseSwift(mouseCoords, IM.GetMouseCoords());
	}
	m_grid.Update(m_score); // Update grid
							// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
}

void GameScene2::Draw(void) {
	m_background.Draw(); // Render background
	m_Image.Draw();
	//m_grid.Draw(); // Render grid*/


	//Second scene texts (Difficulty selection)
	GUI::DrawTextSolid<FontID::FACTORY>("-SNAKE-", { W.GetWidth() >> 1, int(W.GetHeight()*.1f),1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("EASY", { W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("MEDIUM", { W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("HARD", { W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 }, { 0, 0, 0 });

	/*GUI::DrawTextBlended<FontID::FACTORY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated*/
}

