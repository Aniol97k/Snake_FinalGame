#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

//CHECK THE COMMENTS ON "GameSceneMenu.cpp" AS IT APPLIES TO EVERY SCENE OF THIS TYPE

GameSceneMenu::GameSceneMenu(void){
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	int arrowHeight = W.GetHeight() / 2 - 45;
	m_Image = { {W.GetWidth()/2 - 180, arrowHeight,90,90}, ObjectID::ARROW};
}

GameSceneMenu::~GameSceneMenu(void){
}

void GameSceneMenu::OnEntry(void) {
}

void GameSceneMenu::OnExit(void) {
}

void GameSceneMenu::Update(void) {
	
	if (IM.IsKeyDown<KEY_BUTTON_UP>()) {m_Image.transform.y = W.GetHeight() / 2 - 45;}
	else if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) {	m_Image.transform.y = W.GetHeight() / 2 + 30;}
	else if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
		if (m_Image.transform.y == W.GetHeight() / 2 + 30) {std::exit(0);
		}
		else if (m_Image.transform.y == W.GetHeight() / 2 - 45) { SM.SetCurScene<GameSceneDiff>(); } 
	}

}

void GameSceneMenu::Draw(void) {
	m_background.Draw(); 
	m_Image.Draw();

	GUI::DrawTextSolid<FontID::FACTORY>("-SNAKE-",{ W.GetWidth() >> 1, int(W.GetHeight()*.1f),1, 1 },	{ 0, 0, 0 }); 
	GUI::DrawTextSolid<FontID::FACTORY>("PLAY", { W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },{0, 0, 0});
	GUI::DrawTextSolid<FontID::FACTORY>("EXIT", { W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 }, { 0, 0, 0 });

	
}

