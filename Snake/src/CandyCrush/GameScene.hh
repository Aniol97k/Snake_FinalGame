/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "Grid.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class GameSceneMenu : public Scene {
public:
	explicit GameSceneMenu();
	~GameSceneMenu() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_Image;
	
};

class GameSceneDiff : public Scene {
public:
	explicit GameSceneDiff();
	~GameSceneDiff() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_Image;
	
};

class GameSceneEasy : public Scene {
public:
	explicit GameSceneEasy();
	~GameSceneEasy() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_Image, m_Wall, m_Apple,m_Snake,m_cellBG, hearth, hearthEmpty;
	GridSnake m_GridSnake;
	float timer;
	int direction,walls,level,apples,appleCounter,lifes,snakeStartx, snakeSpeed,appleX,appleY,snakeCounter,snakeStarty,m_score{ 0 };
};


class GameSceneMedium : public Scene {
public:
	explicit GameSceneMedium();
	~GameSceneMedium() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_Image, m_Wall, m_Apple, m_Snake, m_cellBG, hearth, hearthEmpty;
	GridSnake m_GridSnake;
	float timer;
	int direction, walls, level, apples, appleCounter, lifes, snakeStartx, snakeSpeed, appleX, appleY, snakeCounter, snakeStarty, m_score{ 0 };
};

class GameSceneHard : public Scene {
public:
	explicit GameSceneHard();
	~GameSceneHard() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_Image, m_Wall, m_Apple, m_Snake, m_cellBG, hearth, hearthEmpty;
	GridSnake m_GridSnake;
	float timer;
	int direction, walls, level, apples, appleCounter, lifes, snakeStartx, snakeSpeed, appleX, appleY, snakeCounter, snakeStarty, m_score{ 0 };
};


class GameSceneDeath : public Scene {
public:
	explicit GameSceneDeath();
	~GameSceneDeath() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_Image;

};

class GameSceneWin: public Scene {
public:
	explicit GameSceneWin();
	~GameSceneWin() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_Image;

};