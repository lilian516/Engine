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
	App::Get()->m_oManager.m_oGraphics.createCam();
	App::Get()->m_oManager.m_vEntity.push_back(App::Get()->m_oManager.m_oGraphics.m_oCamEntity);
	Entity* pMenu = App::Get()->m_oManager.createEntity();
	Entity* pCube = App::Get()->m_oManager.createEntity();
	//Entity* pCubeSky = App::Get()->m_oManager.createEntity();;

	//pCube->m_tTransform.translation({0.0f,1.0f,0.0f});
	Shader* pShader = App::Get()->m_oManager.createShader();

	Texture* pTexture = App::Get()->m_oManager.createTexture("viktor",L"Texture/image.dds");
	Texture* pTextureSkybox = App::Get()->m_oManager.createTexture("apognan", L"Texture/sky.dds");

	Sprite* pMesh = App::Get()->m_oManager.createMesh<Sprite>();
	BoxMesh* pMenuBox = App::Get()->m_oManager.createMesh<BoxMesh>();
	PyramidMesh* pPyramid = App::Get()->m_oManager.createMesh<PyramidMesh>();
	BoxMesh* pBox = App::Get()->m_oManager.createMesh<BoxMesh>();
	Skybox* pSky = App::Get()->m_oManager.createMesh<Skybox>();


	MeshRenderer* pMeshRenderer = pCube->addComponent<MeshRenderer>();
	MeshRenderer* pMeshRendererMenu = pMenu->addComponent<MeshRenderer>();
	//MeshRenderer* pMeshRendererSky = pCubeSky->addComponent<MeshRenderer>();


	//pMeshRendererSky->SetMeshRenderer(pCubeSky, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pSky, pTextureSkybox);
	pMeshRenderer->SetMeshRenderer(pCube, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pMesh, pTexture);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	pMeshRendererMenu->SetMeshRenderer(pMenu, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pMenuBox, pTexture);
	pMeshRendererMenu->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	//pMeshRendererSky->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	createEnemy();
}

void ScriptGame::update() {
	ShowCursor(FALSE);
	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(1)) {
		/*POINT cursorPos;
		GetCursorPos(&cursorPos);*/

		createProjectile();
		
	}
	if (App::Get()->m_oManager.m_oTimer.m_fDifflTime  > 5.0f) {
		createEnemy();
		App::Get()->m_oManager.m_oTimer.m_fDifflTime = 0.0f;
	}

	/*if (App::Get()->m_oManager.m_oInputManager.isKey(65)) {

		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({0.0f,0.0f,0.001f});
		
	}*/
	if (App::Get()->m_oManager.m_oInputManager.isKey(81)) {  //gauche
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ -0.005f,0.0f,0.0f });
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate( 0.0f,0.0f, XMConvertToRadians(-0.5f));
		
	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(83)) { // bas
		
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(0.5f), 0.0f, 0.0f);

	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(68)) {  //droite
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ 0.005f,0.0f,0.0f });
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-10.f), 0.0f, 0.0f);
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(0.5f));

	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(90)) {  //haut
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-0.5f), 0.0f, 0.0f);
		

	}

	//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(App::Get()->m_oManager.m_oInputManager.m_iDeltaY), 0.0f, XMConvertToRadians(App::Get()->m_oManager.m_oInputManager.m_iDeltaX));

	
	
	//ScreenToClient(App::Get()->m_oManager.m_oGraphics.m_hMainWindow, &App::Get()->m_oManager.m_oInputManager.m_pLastMousePos);

	//if (App::Get()->m_oManager.m_oInputManager.m_iDeltaX < 0) {  //gauche
	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(-0.5f));
	//	

	//}
	//if (App::Get()->m_oManager.m_oInputManager.m_iDeltaY > 0) { // bas

	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(0.5f), 0.0f, 0.0f);

	//}
	//if (App::Get()->m_oManager.m_oInputManager.m_iDeltaX > 0) {  //droite
	//	//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ 0.005f,0.0f,0.0f });
	//	//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-10.f), 0.0f, 0.0f);
	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(0.5f));

	//}
	//if (App::Get()->m_oManager.m_oInputManager.m_iDeltaY < 0) {  //haut
	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-0.5f), 0.0f, 0.0f);


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

void ScriptGame::createMenu() {
	Entity* pMenu = App::Get()->m_oManager.createEntity();

	ScriptMenu* pScriptMenu = pMenu->addComponent<ScriptMenu>();
	pScriptMenu->initMenu(pMenu);
}