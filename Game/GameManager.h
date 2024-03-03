#pragma once
#include "pch.h"


class GameManager
{
public :
	GameManager();
	void initGame();
	void mainLoop(HINSTANCE hInstance);
	Manager* m_oManager;
};

