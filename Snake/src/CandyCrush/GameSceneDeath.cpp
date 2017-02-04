/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "BinaryFiles.h"
#include <string>
#include <vector>
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80



GameSceneDeath::GameSceneDeath(void) {

	//Image loads
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_WIN };
	int arrowHeight = W.GetHeight() / 2 - 45;
	m_Image = { { W.GetWidth() / 2 - 180, arrowHeight,90,90 }, ObjectID::ARROW };
	
}

GameSceneDeath::~GameSceneDeath(void) {
}

void GameSceneDeath::OnEntry(void) {
	std::string playerName;
	std::cout << "PLEASE ENTER YOUR NAME: ";
	std::cin >> playerName;	
	BinaryFiles::writeBin(playerName, SM.score);
}

void GameSceneDeath::OnExit(void) {
}

void GameSceneDeath::Update(void) {


	//If's for the arrow's position on the menu
	if (m_Image.transform.y == W.GetHeight() / 2 - 45) {
		m_Image.transform.x = W.GetWidth() / 2 - 200;
	}
	else{ m_Image.transform.x = W.GetWidth() / 2 - 180; }

	//Arrow position depending on the player's key feedback
	if (IM.IsKeyDown<KEY_BUTTON_UP>()) { m_Image.transform.y = W.GetHeight() / 2 - 45; }
	else if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) { m_Image.transform.y = W.GetHeight() / 2 + 30; }
	else if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
		if (m_Image.transform.y == W.GetHeight() / 2 + 30) {
			std::exit(0);
		}
		else if (m_Image.transform.y == W.GetHeight() / 2 - 45) { SM.SetCurScene<GameSceneDiff>(); }
	}

}

void GameSceneDeath::Draw(void) {
	//Render of images and background
	m_background.Draw();
	m_Image.Draw();
	
	//Draw of the texts of the scene
	GUI::DrawTextSolid<FontID::FACTORY>("SCORE: " + std::to_string(SM.score), { W.GetWidth() >> 1, int(W.GetHeight()*.3f),1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("-GAME OVER-", { W.GetWidth() >> 1, int(W.GetHeight()*.1f),1, 1 }, { 0, 0, 0 }); 
	GUI::DrawTextSolid<FontID::FACTORY>("RETRY", { W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 }, { 0, 0, 0 });
	GUI::DrawTextSolid<FontID::FACTORY>("EXIT", { W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 }, { 0, 0, 0 });
		
}
