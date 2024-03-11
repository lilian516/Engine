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
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ENGINE));

	MSG msg;

	// Boucle de messages principale :
	while (true)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		mainLoop();
	}

	return (int)msg.wParam;
}

void Manager::mainLoop() {
	update();
	render();
	
}

void Manager::update() {
	m_oGraphics.update(this);
	m_oInputManager.update();
	m_oTimer.update();
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




Manager::~Manager() {
	while (m_vEntity.size() != 0) {
		delete m_vEntity.back();
		m_vEntity.pop_back();
	}
	while (m_vMesh.size() != 0) {
		delete m_vMesh.back();
		m_vMesh.pop_back();
	}
	while (m_vMeshRenderer.size() != 0) {
		delete m_vMeshRenderer.back();
		m_vMeshRenderer.pop_back();
	}
	while (m_vCollideEntity.size() != 0) {
		delete m_vCollideEntity.back();
		m_vCollideEntity.pop_back();
	}
}


