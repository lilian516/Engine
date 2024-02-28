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

	
	
	/*m_oShader->initializeRootSignature(m_oGraphics->m_d3dDevice);
	m_oShader->initializeShader();
	m_oMesh->buildBoxGeometry();
	m_oShader->initializePipelineState(m_oGraphics->m_d3dDevice);*/
}

void Manager::mainLoop() {
	update();
	render();
	
}

void Manager::update() {
	m_oGraphics->update();
	m_oInputManager->update();
	m_oTimer->update();
	for (int i = 0; i < m_vEntity.size(); i++) {
		m_vEntity[i]->update();
	}
	for (int i = 0; i < m_vShader.size(); i++) {
		m_vShader[i]->update();
	}
	for (int i = 0; i < m_vMesh.size(); i++) {
		m_vMesh[i]->update();
	}
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


