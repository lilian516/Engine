#include "Manager.h"
#include "Resource.h"

Manager::Manager() {

}

void Manager::initManager() {
	m_oGraphics.initGraphics(this);
	m_oInputManager.init();
	m_oTimer.start();
}

int Manager::runWindow(HINSTANCE hInstance) {
	while (true) {
		mainLoop();
	}
	return 0;
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

Mesh* Manager::createMesh(std::string name) {
	m_oGraphics.m_cCommandList->Reset(m_oGraphics.m_cDirectCmdListAlloc, nullptr);
	if (name == "box") {
		BoxMesh* pMesh = new BoxMesh();
		pMesh->buildGeometry(m_oGraphics.m_d3dDevice,m_oGraphics.m_cCommandList);
		m_vMesh.push_back(pMesh);

		m_oGraphics.m_cCommandList->Close();
		ID3D12CommandList* cmdsLists[] = { m_oGraphics.m_cCommandList };
		m_oGraphics.m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

		// Wait until initialization is complete.
		m_oGraphics.flushCommandQueue();
		return pMesh;
	}
	else if (name == "pyramid") {
		PyramidMesh* pMesh = new PyramidMesh();
		pMesh->buildGeometry(m_oGraphics.m_d3dDevice, m_oGraphics.m_cCommandList);
		m_vMesh.push_back(pMesh);

		m_oGraphics.m_cCommandList->Close();
		ID3D12CommandList* cmdsLists[] = { m_oGraphics.m_cCommandList };
		m_oGraphics.m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

		// Wait until initialization is complete.
		m_oGraphics.flushCommandQueue();
		return pMesh;
	}
	else if (name == "pen") {
		PenMesh* pMesh = new PenMesh();
		pMesh->buildGeometry(m_oGraphics.m_d3dDevice, m_oGraphics.m_cCommandList);
		m_vMesh.push_back(pMesh);

		m_oGraphics.m_cCommandList->Close();
		ID3D12CommandList* cmdsLists[] = { m_oGraphics.m_cCommandList };
		m_oGraphics.m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

		// Wait until initialization is complete.
		m_oGraphics.flushCommandQueue();
		return pMesh;
	}
	else {
		BoxMesh* pMesh = new BoxMesh();
		pMesh->buildGeometry(m_oGraphics.m_d3dDevice, m_oGraphics.m_cCommandList);
		m_vMesh.push_back(pMesh);

		m_oGraphics.m_cCommandList->Close();
		ID3D12CommandList* cmdsLists[] = { m_oGraphics.m_cCommandList };
		m_oGraphics.m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

		// Wait until initialization is complete.
		m_oGraphics.flushCommandQueue();
		return pMesh;
	}
	


	
}

Manager::~Manager() {
	/*while (m_vEntity.size() != 0) {
		delete m_vEntity[0];
	}
	while (m_vShader.size() != 0) {
		delete m_vShader[0];
	}
	while (m_vMesh.size() != 0) {
		delete m_vMesh[0];
	}
	while (m_vMeshRenderer.size() != 0) {
		delete m_vMeshRenderer[0];
	}
	while (m_vCollideEntity.size() != 0) {
		delete m_vCollideEntity[0];
	}*/
}


