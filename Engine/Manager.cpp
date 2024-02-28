#include "Manager.h"

Manager::Manager() {

}

void Manager::initManager() {
	m_oGraphics = new Graphics();
	m_oGraphics->initGraphics();
	m_oInputManager = new InputManager();
	m_oInputManager->init();
}

void Manager::mainLoop() {
	
	
	update();
	render();
	
	
}

void Manager::update() {
	m_oGraphics->update();
	m_oInputManager->update();
}

void Manager::render() {
	m_oGraphics->render();
}