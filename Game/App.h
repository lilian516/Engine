#pragma once
#include "framework.h"
class App
{
public :
	App();
	void initApp();
	void runApp(HINSTANCE hInstance);
	Manager m_oManager;
	static App* pInstance;
	static void Init();
	static App* Get();
};

