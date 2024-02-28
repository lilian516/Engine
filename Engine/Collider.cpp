#include "Collider.h"
#include "MathHelper.h"

Collider::Collider() {

}

Collider::~Collider() {

}

void Collider::setCollider() {
	setComponent(1);
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
		if (distanceCalcul())
	}
}