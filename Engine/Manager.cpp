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
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
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




Manager::~Manager() {
	while (m_vEntity.size() != 0) {
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
	}
}


