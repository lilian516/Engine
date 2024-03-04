#include "GameManager.h"
#include "Move.h"
#include "EnemyManager.h"
#include "Projectile.h"

GameManager::GameManager() {

}

void GameManager::initGame() {
    m_oManager = new Manager();
    Shader* oShader = new Shader();

    RectangleMesh* oButtonMesh = new RectangleMesh();
    BoxMesh* oBoxMesh = new BoxMesh();
    PyramidMesh* oPyramidMesh = new PyramidMesh();
    m_oManager->m_vMesh.push_back(oButtonMesh);
    m_oManager->m_vMesh.push_back(oBoxMesh);
    m_oManager->m_vMesh.push_back(oPyramidMesh);
    m_oManager->m_vShader.push_back(oShader);

    m_oManager->initManager();
    
    

    MeshRenderer* oMeshRenderer = new MeshRenderer();
    


    Entity* oButton = new Entity();
    oButton->initEntity();
    oButton->addComponent(oMeshRenderer);

    oMeshRenderer->buildConstantBuffers(m_oManager->m_oGraphics->m_d3dDevice, m_oManager->m_oGraphics->m_dConstantBufferViewHeapDescriptor);
    oMeshRenderer->SetMeshRenderer(oButton, m_oManager->m_oGraphics->m_d3dDevice, oShader, oButtonMesh);

    oButton->addComponent(oMeshRenderer);


    
    m_oManager->addEntity(oButton);

    m_oEnemyManager = new EnemyManager();
    
    
}

void GameManager::mainLoop(HINSTANCE hInstance) {
    char game = Start;
    
    while (true) {

        switch (game) {
            case Start:
                
                if (m_oManager->m_oInputManager->isKeyDown(1) == true) {
                    if (m_oManager->m_vEntity.size() > 0) {
                        m_oManager->m_vEntity.pop_back();
                        game = Play;
                        
                    }
                }
                break;

            case Play:
                if (m_oManager->m_oTimer->m_iFrameCount % 5000 == 0 ) {
                    game = Spawn;
                }
                if (m_oManager->m_oInputManager->isKeyDown(1) == true) {
                    Projectile* oProjectile = new Projectile();
                    oProjectile->initProjectile(m_oManager, m_oManager->m_vShader[0], m_oManager->m_vMesh[2]);
                }
                break;
            case Spawn:
                m_oEnemyManager->createEnemy(m_oManager);
                game = Play;
                
                
                
               



                ///////////////////////////////////////////////////////////////////////test
               /* Shader* oShader = new Shader();

                RectangleMesh* oButtonMesh = new RectangleMesh();

                MeshRenderer* oMeshRenderer = new MeshRenderer();
                m_oManager->m_vMesh.push_back(oButtonMesh);

                m_oManager->m_vShader.push_back(oShader);
                m_oManager->m_vMeshRenderer.push_back(oMeshRenderer);
                
                m_oManager->m_oGraphics->m_cCommandList->Reset(m_oManager->m_oGraphics->m_cDirectCmdListAlloc, nullptr);
                oMeshRenderer->buildConstantBuffers(m_oManager->m_oGraphics->m_d3dDevice, m_oManager->m_oGraphics->m_dConstantBufferViewHeapDescriptor);
                m_oManager->m_oGraphics->m_cCommandList->Close();
                Entity* oButton = new Entity();
                oButton->initEntity();
                oMeshRenderer->SetMeshRenderer(oButton, m_oManager->m_oGraphics->m_d3dDevice, oShader, oButtonMesh);
                oButton->addComponent(oMeshRenderer);*/
                

                
                

                

                ////////////////////////////////////////////////////////////////////////////////

                //m_oManager->addEntity(oButton);

                break;

        }

        
        m_oManager->runWindow(hInstance);
    }
    
  
    
    
}
