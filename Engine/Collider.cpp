#include "Collider.h"

Collider::Collider() {

}

Collider::~Collider() {

}

void Collider::setCollider(Entity *oEntity) {
	initComponent(1, *oEntity);
	m_cCollision = NoCollide;
}

void Collider::update() {
	switch (m_cCollision)
	{
	case FirstCollide:
		enterCollision();
		m_cCollision = Collide;
		break;
	case Collide:
		stayCollision();
		break;
	case LastCollide:
		exitCollision();
		m_cCollision = LastCollide;
		break;
	case NoCollide:
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

}