/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "GameScene.hh"
#pragma endregion TODO


namespace GameEngine {
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::CANDY>("fnt/candy.ttf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);
		R.LoadTexture<ObjectID::BG_00>("gfx/bg.jpg");
		R.LoadTexture<ObjectID::ARROW>("gfx/arrow.png");
		R.LoadTexture<ObjectID::BG_GAME>("gfx/SnakeGameBg.png");
		R.LoadTexture<ObjectID::BG_CELL>("gfx/cellBackground.png");
		R.LoadTexture<ObjectID::SNAKE>("gfx/snake.png");
		R.LoadTexture<ObjectID::APPLE>("gfx/apple.png");
		R.LoadTexture<ObjectID::WALL>("gfx/wall.png");
		R.LoadTexture<ObjectID::BG_DEATH>("gfx/BgDeath.png");
		R.LoadTexture<ObjectID::FULL_HEARTH>("gfx/FullHearth.png");
		R.LoadTexture<ObjectID::EMPTY_HEARTH>("gfx/EmptyHearth.png");
		R.LoadTexture<ObjectID::BG_WIN>("gfx/BgWin.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD>("gfx/snake.png");
		R.LoadTexture<ObjectID::BAR>("gfx/bar.png");
	}

	//GameScenes of the game
	void AddScenes(void) {
		SM.AddScene<GameSceneMenu>();

		SM.AddScene<GameSceneDiff>();

		SM.AddScene<GameSceneEasy>();
		SM.AddScene<GameSceneMedium>();
		SM.AddScene<GameSceneHard>();
		
		SM.AddScene<GameSceneDeath>();

		SM.AddScene<GameSceneWin>();

		//Setting the menu GameScene as the first one.
		SM.SetCurScene<GameSceneMenu>();
	}
	
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); 
		LoadMedia(); 
		AddScenes(); 
		bool m_isRunning{ true }; 
		Scene *&m_curScene(SM.GetCurScene()); 
		while (!IM.HasQuit() && m_isRunning) { 
			TM.FPSBegin(); 
			#pragma region GAME_UPDATE
				switch (m_curScene->GetState()) { 
					case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; 
					case SceneState::EXIT:		m_isRunning = false; break; 
					case SceneState::SLEEP: default:;
				}
			#pragma endregion
			#pragma region GAME_DRAW
				TM.FPSEnd([&]() { 
					if (m_curScene->CheckState<SceneState::RUNNING>()) { 
						R.Clear();			
						m_curScene->Draw(); 
						R.Render();			
					}});
			#pragma endregion
		}
	}
}