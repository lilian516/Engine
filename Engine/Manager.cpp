#include "Manager.h"
#include "Resource.h"

Manager::Manager() {

}

void Manager::initManager() {
	m_oGraphics.initGraphics(this);
	m_oInputManager.init();
	m_oTimer.start();
}



void Manager::mainLoop() {
	while (true) {
		update();
		render();
	}
	
	
}

void Manager::update() {
	m_oGraphics.update(this);
	m_oInputManager.update();
	m_oTimer.update();
	
	for (int i = 0; i < m_vShader.size(); i++) {
		m_vShader[i]->update();
	}
	for (int i = 0; i < m_vMesh.size(); i++) {
		m_vMesh[i]->update();
	}
}

void Manager::render() {
	
	m_oGraphics.render(this);
}

void Manager::addEntity(Entity* oEntity) {
	m_vEntity.push_back(oEntity);
}

Entity* Manager::createEntity() {
	Entity* oEntity = new Entity();
	oEntity->initEntity();
	m_vEntity.push_back(oEntity);
	return oEntity;
}

Shader* Manager::createShader() {
	Shader* oShader = new Shader();
	oShader->initializeRootSignature(m_oGraphics.m_d3dDevice);
	oShader->initializeShader();
	oShader->initializePipelineState(m_oGraphics.m_d3dDevice);
	m_vShader.push_back(oShader);
	return oShader;
}

Texture* Manager::createTexture(std::string name, wstring filename) {
	Texture* oTexture = new Texture();
	oTexture->loadTextureFromFile(name, filename,m_oGraphics.m_d3dDevice,&m_oGraphics);
	oTexture->buildSRVDescriptorHeap(m_oGraphics.m_d3dDevice,name, &m_oGraphics);
	m_vTexture.push_back(oTexture);
	return oTexture;
}



Manager::~Manager() {
	for (Entity* ptr : m_vEntity) {
		delete ptr;
	}
	m_vEntity.clear();
	for (Shader* ptr : m_vShader) {
		delete ptr;
	}
	m_vShader.clear();
	for (Mesh* ptr : m_vMesh) {
		delete ptr;
	}
	m_vMesh.clear();
	for (Entity* ptr : m_vCollideEntity) {
		delete ptr;
	}
	m_vCollideEntity.clear();
	
}


