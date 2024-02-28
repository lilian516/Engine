#include "Manager.h"

Manager::Manager() {

}

void Manager::initManager() {
	m_oGraphics = new Graphics();
	m_oGraphics->initGraphics();
	m_oInputManager = new InputManager();
	m_oInputManager->init();
	m_oTimer = new Timer();
	m_oTimer->start();
}

void Manager::mainLoop() {
	
	
	update();
	render();
	
	
}

void Manager::update() {
	m_oGraphics->update();
	m_oInputManager->update();
	m_oTimer->update();
}

void Manager::render() {
	m_oGraphics->render();
}

void Manager::addEntity(Entity* oEntity) {
	m_vEntity.push_back(oEntity);
}

Manager::~Manager() {
	delete m_oGraphics;
	delete m_oInputManager;
	delete m_oTimer;

}