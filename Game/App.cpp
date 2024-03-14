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
	
	m_pScriptManager = pEntityGame->addComponent<ScriptManager>();
	pScriptMenu->initMenu(pEntityGame);
	pScriptMenu->setScriptManager(m_pScriptManager);
	pScriptGame->initGame(pEntityGame);
	m_pScriptManager->setScriptManager<ScriptMenu,ScriptGame>(pEntityGame, pScriptMenu, pScriptGame);
	
}

void App::runApp(HINSTANCE hInstance) {
	m_oManager.mainLoop(hInstance);
}

App::~App() {
	
}

