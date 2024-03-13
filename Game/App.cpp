#include "App.h"
#include "ScriptGame.h"
#include "ScriptMenu.h"

App::App(){

}

App* App::pInstance = nullptr;

void App::Init()
{
	App::pInstance = new App();
}

App* App::Get()
{
	return App::pInstance;
}
void App::initApp() {
	m_oManager.initManager();
	
	
	Entity* pEntityGame = m_oManager.createEntity();
	ScriptMenu* pScriptMenu = new ScriptMenu();
	ScriptGame* pScriptGame = new ScriptGame();
	pScriptGame->initGame(pEntityGame);
	pScriptMenu->initMenu(pEntityGame);
	ScriptManager* pScriptManager = pEntityGame->addComponent<ScriptManager>();
	pScriptManager->setScriptManager<ScriptMenu,ScriptGame>(pEntityGame, pScriptMenu, pScriptGame);
	pScriptMenu->setScriptManager(pScriptManager);
	//template<typename T>
	//test(T a);
	//pEntity->ChangeCurrentScript(pScript);
}

void App::runApp() {
	m_oManager.mainLoop();
}

//Init
//{
//	creation des inst
//}
//Update