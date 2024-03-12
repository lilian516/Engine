#include "ScriptGame.h"
#include "App.h"
#include "framework.h"
#include "ScriptProjectile.h"
#include "ScriptEnemy.h"
ScriptGame::ScriptGame() {

}

void ScriptGame::initGame(Entity* oEntity) {
	setScript(oEntity);
	App::Get()->m_oManager.m_oGraphics.createCam();
	App::Get()->m_oManager.m_vEntity.push_back(App::Get()->m_oManager.m_oGraphics.m_oCamEntity);
	Entity* pCube = App::Get()->m_oManager.createEntity();
	Entity* pCubeSky = App::Get()->m_oManager.createEntity();;
	//pCube->m_tTransform.translation({0.0f,1.0f,0.0f});
	Shader* pShader = App::Get()->m_oManager.createShader();
	Texture* pTexture = App::Get()->m_oManager.createTexture("test",L"Texture/image.dds");
	Texture* pTextureSkybox = App::Get()->m_oManager.createTexture("test",L"Texture/sky.dds");
	Sprite* pMesh = App::Get()->m_oManager.createMesh<Sprite>();
	PyramidMesh* pPyramid = App::Get()->m_oManager.createMesh<PyramidMesh>();
	BoxMesh* pBox = App::Get()->m_oManager.createMesh<BoxMesh>();
	Skybox* pSky = App::Get()->m_oManager.createMesh<Skybox>();
	MeshRenderer* pMeshRenderer = pCube->addComponent<MeshRenderer>();
	MeshRenderer* pMeshRendererSky = pCubeSky->addComponent<MeshRenderer>();
	pMeshRendererSky->SetMeshRenderer(pCubeSky, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pSky, pTextureSkybox);
	pMeshRenderer->SetMeshRenderer(pCube, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pMesh, pTexture);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	pMeshRendererSky->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
}

void ScriptGame::update() {

	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(1)) {
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		createProjectile();
		
	}
	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(2)) {
		App::Get()->m_oManager.m_vEntity.pop_back();
	}
	if (App::Get()->m_oManager.m_oTimer.m_fDifflTime  > 5.0f) {
		createEnemy();
		App::Get()->m_oManager.m_oTimer.m_fDifflTime = 0.0f;
	}
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