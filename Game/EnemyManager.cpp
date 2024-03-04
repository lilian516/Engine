#include "EnemyManager.h"
#include "Enemy.h"


EnemyManager::EnemyManager() {

}

void EnemyManager::initEnemyManager(Manager *oManager) {


	
	
	//m_oMesh->buildGeometry(oManager->m_oGraphics->m_d3dDevice, oManager->m_oGraphics->m_cCommandList);
	//oManager->m_vMesh.push_back(m_oMesh);
}

void EnemyManager::createEnemy(Manager* oManager) {

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(-2.0f, 2.0f);
	float x = distr(eng);
	float y = distr(eng);
	float z = distr(eng);

	Enemy *oEnemy = new Enemy();
	oEnemy->initEnemy(oManager->m_oGraphics, oManager->m_vShader[0], oManager->m_vMesh[1]);
	XMFLOAT4 vect{ x,y,z,0.0f};
	oEnemy->m_tTransform.translation(vect);
	oEnemy->m_tTransform.updateTransform();
	oManager->m_vEntity.push_back(oEnemy);
	m_vEnemy.push_back(oEnemy);

}