#pragma once
#include "Grid.hh"
#include "Scene.hh"


// GameScene for the menu
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

//GameScene for the difficulty level selection
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

//GameScene for the easy mode
class GameSceneEasy : public Scene {
public:
	explicit GameSceneEasy();
	~GameSceneEasy() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_HearthFull1, m_HearthFull2, m_HearthFull3, m_Wall, m_Apple,m_Snake,m_cellBG,hearthEmpty1, hearthEmpty2, hearthEmpty3, timerBar;
	GridSnake m_GridSnake;
	float timer; //Timer for the snake speed
	int direction,walls,level,apples,appleCounter, toAdd,lifes,snakeStartx, snakeSpeed,appleX,appleY,snakeCounter,snakeStarty,m_score{ 0 };
	int cells, snakeX, snakeY, speed, timerXML; //XML variables to read
	int timerBarAux, lastX, lastY, lastX2, lastY2, barLenght;
	int Xpos[50]; //Arrays for the X and Y positions of the snake
	int Ypos[50];
	bool keyPressed; //Bool for when a key is pressed to start the snake movement

};

//GameScene for the medium mode
class GameSceneMedium : public Scene {
public:
	explicit GameSceneMedium();
	~GameSceneMedium() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background, m_HearthFull1, m_HearthFull2, m_HearthFull3,m_Wall, m_Apple, m_Snake, m_cellBG, hearthEmpty1, hearthEmpty2, hearthEmpty3, timerBar;
	GridSnake m_GridSnake;
	float timer; 
	int direction, walls, level, apples, appleCounter, lifes,toAdd, snakeStartx, snakeSpeed, appleX, appleY, snakeCounter, snakeStarty, m_score{ 0 };
	int cellsM, snakeXM, snakeYM, speedM, timerXMLM;
	int timerBarMAux, lastX, lastY, lastX2, lastY2, barLenght;
	int Xpos[50]; 
	int Ypos[50];
	bool keyPressed;  
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
	Sprite m_background, m_HearthFull1, m_HearthFull2, m_HearthFull3, m_Wall, m_Apple, m_Snake, m_cellBG, hearthEmpty1, hearthEmpty2, hearthEmpty3, timerBar;
	GridSnake m_GridSnake;
	float timer;
	int direction, walls, level, apples, appleCounter, lifes, toAdd, snakeStartx, snakeSpeed, appleX, appleY, snakeCounter, snakeStarty, m_score{ 0 };
	int cellsH, snakeXH, snakeYH, speedH,timerXMLH;
	int timerBarHAux, lastX, lastY, lastX2, lastY2, barLenght;
	int Xpos[50];
	int Ypos[50];
	bool keyPressed;
};

//GameScene when player dies
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
	bool asked;
};

//GameScene when player wins
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
	bool asked;

};