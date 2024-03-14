#include "ScriptGame.h"
#include "App.h"
#include "framework.h"
#include "ScriptProjectile.h"
#include "ScriptEnemy.h"
#include "ScriptMenu.h"
ScriptGame::ScriptGame() {

}

void ScriptGame::initGame(Entity* oEntity) {
	setScript(oEntity);
	ShowCursor(FALSE);

	//création de la caméra
	App::Get()->m_oManager.m_oGraphics.createCam();
	App::Get()->m_oManager.addEntity(App::Get()->m_oManager.m_oGraphics.m_oCamEntity);

	PyramidMesh* pPyramid = App::Get()->m_oManager.createMesh<PyramidMesh>();
	PenMesh* pPen = App::Get()->m_oManager.createMesh<PenMesh>();
	BoxMesh* pBox = App::Get()->m_oManager.createMesh<BoxMesh>();
	Texture* pTexture = App::Get()->m_oManager.createTexture("viktor", L"Texture/image.dds");
	Texture* pTextureLaser = App::Get()->m_oManager.createTexture("laser",L"Texture/Laser.dds");


	/// création de la Skybox
	Skybox* pSky = App::Get()->m_oManager.createMesh<Skybox>();
	Texture* pTextureSkybox = App::Get()->m_oManager.createTexture("sky", L"Texture/sky.dds");
	Entity* pCubeSky = App::Get()->m_oManager.createEntity();
	MeshRenderer* pMeshRendererSky = pCubeSky->addComponent<MeshRenderer>();
	pCubeSky->scale({ 800.0f,800.0f,800.0f });
	pMeshRendererSky->SetMeshRenderer(pCubeSky, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, App::Get()->m_oManager.m_vShader[0], pSky, pTextureSkybox);
	




	////pCube->m_tTransform.translation({0.0f,1.0f,0.0f});
	//Entity* pMenu = App::Get()->m_oManager.createEntity();
	//Entity* pCube = App::Get()->m_oManager.createEntity();

	
	

	//Sprite* pMesh = App::Get()->m_oManager.createMesh<Sprite>();
	//BoxMesh* pMenuBox = App::Get()->m_oManager.createMesh<BoxMesh>();
	
	
	


	//MeshRenderer* pMeshRenderer = pCube->addComponent<MeshRenderer>();
	//MeshRenderer* pMeshRendererMenu = pMenu->addComponent<MeshRenderer>();
	


	
	//pMeshRenderer->SetMeshRenderer(pCube, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pMesh, pTexture);
	//pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	//pMeshRendererMenu->SetMeshRenderer(pMenu, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pMenuBox, pTexture);
	//pMeshRendererMenu->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	
}

void ScriptGame::update() {
	
	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(1)) {
		createProjectile();
		
	}
	if (App::Get()->m_oManager.m_oTimer.m_fDifflTime  > 5.0f) {
		createEnemy();
		App::Get()->m_oManager.m_oTimer.m_fDifflTime = 0.0f;
	}

	
	
	if (App::Get()->m_oManager.m_oInputManager.isKey(81)) {  //gauche
		
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(),
			2.0f, 0.0f, 0.0f, XMConvertToRadians(-0.4f));
		
	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(83)) { // bas
		
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(),
			2,XMConvertToRadians(0.4f), 0.0f, 0.0f);

	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(68)) {  //droite
		
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(),
			2,0.0f, 0.0f, XMConvertToRadians(0.4f));

	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(90)) {  //haut
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(),
			2.0f , XMConvertToRadians(-0.4f), 0.0f, 0.0f);

	}

	//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(App::Get()->m_oManager.m_oInputManager.m_iDeltaY), 0.0f, XMConvertToRadians(App::Get()->m_oManager.m_oInputManager.m_iDeltaX));

	
	
	//ScreenToClient(App::Get()->m_oManager.m_oGraphics.m_hMainWindow, &App::Get()->m_oManager.m_oInputManager.m_pLastMousePos);

	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaX < 0) {  //gauche
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(-0.5f));
		

	}
	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaY > 0) { // bas

		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(0.5f), 0.0f, 0.0f);

	}
	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaX > 0) {  //droite
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ 0.005f,0.0f,0.0f });
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-10.f), 0.0f, 0.0f);
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(0.5f));

	}
	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaY < 0) {  //haut
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-0.5f), 0.0f, 0.0f);
	}


	//}
	
	
	
	// Z 90   Q 81   S83 D  68
	
	
}

void ScriptGame::createProjectile() {
	Entity* pProjectile = App::Get()->m_oManager.createEntity();

	ScriptProjectile* pScript = pProjectile->addComponent<ScriptProjectile>();
	pScript->initProjectile(pProjectile);
}

void ScriptGame::createEnemy() {
	Entity* pEnemy = App::Get()->m_oManager.createEntity();

	ScriptEnemy* pScript = pEnemy->addComponent<ScriptEnemy>();
	pScript->initEnemy(pEnemy);
}

