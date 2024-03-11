#include "ColliderGame.h"


ColliderGame::ColliderGame() {

}

void ColliderGame::enterCollision() {
	Entity* oEntityCollider = nullptr;
	for (int i = 0; i < m_oEntity->m_vComponents.size(); i++ ) {
		if (Collider* collider = dynamic_cast<Collider*>(m_oEntity->m_vComponents[i])) {
			oEntityCollider = collider->getCollidingEntity();
		}
	}
	App::Get()->m_oManager.deleteEntity(m_oEntity);
	App::Get()->m_oManager.deleteEntity(oEntityCollider);
}