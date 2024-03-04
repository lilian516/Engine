#pragma once
#include "pch.h"
#include "Enemy.h"

class EnemyManager;

class GameManager
{
public :
	GameManager();
	void initGame();
	void mainLoop(HINSTANCE hInstance);
	Manager* m_oManager;
	enum StateGame { Start, Play, Spawn};
	EnemyManager* m_oEnemyManager;
	
};

