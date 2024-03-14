#include "Manager.h"
#include "Resource.h"

Manager::Manager() {

}

void Manager::initManager() {
	m_oGraphics.initGraphics(this);
	m_oInputManager.init(&m_oGraphics);
	m_oTimer.start();
}



void Manager::mainLoop(HINSTANCE hInstance) {


	bool bIsRunning = true;
	
	MSG msg;
	while (bIsRunning) {


		

		// Boucle de messages principale :
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				bIsRunning = false;
			}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			
		}
		else {
			update();
			render();
		}
		
	}
	delete this;
	
	
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
	m_vTexture.insert(std::make_pair(name,oTexture));
	oTexture->buildSRVDescriptorHeap(m_oGraphics.m_d3dDevice,name, &m_oGraphics,m_vTexture);
	return oTexture;
}

void Manager::addCollideEntity(Entity* oEntity) {
	m_vCollideEntity.push_back(oEntity);
}

void Manager::deleteEntity(Entity* oEntity) {
	for (auto it = m_vEntity.begin(); it != m_vEntity.end();) {
		// Vérifiez si l'élément actuel correspond à celui que vous recherchez
		if (*it == oEntity) {
			// Suppression de l'élément du vecteur et mise à jour de l'itérateur
			m_vEntity.erase(it);
			break;
		}
		else {
			// Déplacez-vous vers l'élément suivant dans le vecteur
			++it;
		}

	}
	for (auto it = m_vCollideEntity.begin(); it != m_vCollideEntity.end();) {
		// Vérifiez si l'élément actuel correspond à celui que vous recherchez
		if (*it == oEntity) {
			// Suppression de l'élément du vecteur et mise à jour de l'itérateur
			m_vCollideEntity.erase(it);
			break;
		}
		else {
			// Déplacez-vous vers l'élément suivant dans le vecteur
			++it;
		}

	}

	delete oEntity;
}


Manager::~Manager() {
	for (Entity* ptr : m_vEntity) {
		delete ptr;
	}
	m_vEntity.clear();
	
	for (Mesh* ptr : m_vMesh) {
		delete ptr;
	}
	m_vMesh.clear();
	/*for (Entity* ptr : m_vCollideEntity) {
		delete ptr;
	}
	m_vCollideEntity.clear();
	*/
	/*for (Texture* ptr : m_vTexture) {
		delete ptr;
	}
	m_vTexture.clear();*/
	
}


