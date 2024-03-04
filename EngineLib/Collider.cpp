#include "pch.h"
#include "Collider.h"
#include "MathHelper.h"
#include "Transform.h"


Collider::Collider() {

}

Collider::~Collider() {

}

void Collider::setCollider(Entity* oEntity) {
	initComponent(1,oEntity);
	m_cCollision = NoCollision;
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
		if (distanceCalcul(m_oEntity.getTransform().m_vPosition, entity->getTransform().m_vPosition) < 0) {
			m_cCollision = FirstCollision;
		}
	}
}