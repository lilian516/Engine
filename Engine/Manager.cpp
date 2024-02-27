#include "Manager.h"

Manager::Manager() {

}

void Manager::initManager() {
	m_oGraphics = new Graphics();
	m_oGraphics->initGraphics();
}

void Manager::mainLoop() {
	
	
	update();
	render();
	
	
}

void Manager::update() {
	m_oGraphics->update();
}

void Manager::render() {
	m_oGraphics->render();
}