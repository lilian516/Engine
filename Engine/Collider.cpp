#include "Collider.h"
#include "MathHelper.h"
#include "Transform.h"

Collider::Collider() {

}

Collider::~Collider() {

}

void Collider::setCollider(Entity* oEntity, vector<Entity*> vColliderEntity) {
	initComponent(1,oEntity);
	m_cCollision = NoCollision;
	m_vColliderEntity = vColliderEntity;
}

void Collider::update() {
	switch (m_cCollision)
	{
	case FirstCollision:
		enterCollision();
		m_cCollision = Collision;
		break;
	case Collision:
		stayCollision();
		break;
	case LastCollision:
		exitCollision();
		m_cCollision = NoCollision;
		break;
	case NoCollision:
		noCollision();
		break;
	default:
		break;
	}
}

void Collider::enterCollision() {

}

void Collider::stayCollision() {

}

void Collider::exitCollision() {

}

void Collider::noCollision() {
	for (Entity* entity : m_vColliderEntity) {
		if (entity != m_oEntity){
			if (std::abs(entity->m_aBox.pCenter.x - m_oEntity->m_aBox.pCenter.x) > (entity->m_aBox.vRadius.x + m_oEntity->m_aBox.vRadius.x)) {
				return;
			}
			if (std::abs(entity->m_aBox.pCenter.y - m_oEntity->m_aBox.pCenter.y) > (entity->m_aBox.vRadius.y + m_oEntity->m_aBox.vRadius.y)) {
				return;
			}
			if (std::abs(entity->m_aBox.pCenter.z - m_oEntity->m_aBox.pCenter.z) > (entity->m_aBox.vRadius.z + m_oEntity->m_aBox.vRadius.z)) {
				return;
			}
			m_cCollision = FirstCollision;
			m_eCollidingEntity = entity;
		}
	}
}