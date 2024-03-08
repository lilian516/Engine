#include "ScriptProjectile.h"
#include "App.h"

ScriptProjectile::ScriptProjectile() {

}

void ScriptProjectile::initProjectile(Entity* oEntity) {
	setScript(oEntity);
	
	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0], 
		App::Get()->m_oManager.m_vMesh[1], 
		App::Get()->m_oManager.m_vTexture[0]);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice, App::Get()->m_oManager.m_oGraphics.m_dConstantBufferViewHeapDescriptor);
}

void ScriptProjectile::update() {

}