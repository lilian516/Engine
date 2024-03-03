#include "GameManager.h"

GameManager::GameManager() {

}

void GameManager::initGame() {
    m_oManager = new Manager();
    Mesh* oMesh = new Mesh();
    Shader* oShader = new Shader();

    MeshRenderer* oMeshRenderer = new MeshRenderer();
    m_oManager->m_vMesh.push_back(oMesh);

    m_oManager->m_vShader.push_back(oShader);
    m_oManager->m_vMeshRenderer.push_back(oMeshRenderer);


    Entity* oEntity = new Entity();
    oEntity->initEntity();


    m_oManager->initManager();
    oMeshRenderer->SetMeshRenderer(oEntity, m_oManager->m_oGraphics->m_d3dDevice, oShader, oMesh);

    oEntity->AddComponents(oMeshRenderer);



    m_oManager->addEntity(oEntity);
}

void GameManager::mainLoop(HINSTANCE hInstance) {
    while (true) {
        if (m_oManager->m_oInputManager->isKey(65) == true) {
            int a = 1;
        }
        m_oManager->runWindow(hInstance);
        int b = 5;
    }
    
    
}
