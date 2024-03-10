#include "ScriptProjectile.h"
#include "App.h"

ScriptProjectile::ScriptProjectile() {
	m_oEntity = nullptr;
}

void ScriptProjectile::initProjectile(Entity* oEntity) {
	setScript(oEntity);
	
	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0], 
		App::Get()->m_oManager.m_vMesh[1], 
		App::Get()->m_oManager.m_vTexture[0]);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice, App::Get()->m_oManager.m_oGraphics.m_dConstantBufferViewHeapDescriptor);
	Collider* pCollider = oEntity->addComponent<Collider>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);

}

void ScriptProjectile::update() {
	m_oEntity->m_tTransform.move(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 2);
	if (m_oEntity->m_tTransform.m_vPosition.z > 5) {
		for (auto it = App::Get()->m_oManager.m_vEntity.begin(); it != App::Get()->m_oManager.m_vEntity.end();) {
			// V�rifiez si l'�l�ment actuel correspond � celui que vous recherchez
			if (*it == m_oEntity) {
				// Suppression de l'�l�ment du vecteur et mise � jour de l'it�rateur
				it = App::Get()->m_oManager.m_vEntity.erase(it);
				delete m_oEntity;
			}
			else {
				// D�placez-vous vers l'�l�ment suivant dans le vecteur
				++it;
			}
			
		}
	}
	
}