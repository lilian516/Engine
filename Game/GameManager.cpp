#include "GameManager.h"
#include "Move.h"
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

    
    oEntity->addComponent(m_oManager->m_vMeshRenderer[0]);
    Move* move = new Move();
    move->setScript(oEntity);
    oEntity->addComponent(move);

    m_oManager->initManager();
    oMeshRenderer->SetMeshRenderer(oEntity, m_oManager->m_oGraphics->m_d3dDevice, oShader, oMesh);

    oEntity->addComponent(oMeshRenderer);


    
    m_oManager->addEntity(oEntity);
}

void GameManager::mainLoop(HINSTANCE hInstance) {
    while (true) {
        if (m_oManager->m_oInputManager->isKeyDown(2) == true) {
            
            m_oManager->m_vEntity.pop_back();
            
        }
        else if (m_oManager->m_oInputManager->isKeyDown(1) == true) {
            
           /* Entity* oEntity2 = new Entity();
            oEntity2->initEntity();

            MeshRenderer* oMeshRenderer = new MeshRenderer();
            m_oManager->m_vMeshRenderer.push_back(oMeshRenderer);
            oMeshRenderer->SetMeshRenderer(oEntity2, m_oManager->m_oGraphics->m_d3dDevice, m_oManager->m_vShader[0], m_oManager->m_vMesh[0]);
            oEntity2->addComponent(oMeshRenderer);


            Move* move = new Move();
            move->setScript(oEntity2);
            oEntity2->addComponent(move);
            m_oManager->addEntity(oEntity2);*/
            

            
        }
        m_oManager->runWindow(hInstance);
       
        
    }
    
    
}
