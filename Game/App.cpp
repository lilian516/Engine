#include "App.h"
#include "ScriptGame.h"

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

	Entity* pEntity = m_oManager.createEntity();
	ScriptGame* pScript = pEntity->addComponent<ScriptGame>();
	pScript->initGame(pEntity);
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