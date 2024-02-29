#include "Collider.h"

Collider::Collider() {

}

Collider::~Collider() {

}

void Collider::setCollider(Entity* oEntity) {
	initComponent(1,*oEntity);
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
	float fDistance;
	XMVECTOR vEntityPosition;
	XMFLOAT4 vPos= m_oEntity.getTransform().m_vPosition;
	XMVECTOR vPosition = XMLoadFloat4(&vPos);

	for (Entity* entity : m_vColliderEntity) {
		vPos = entity->getTransform().m_vPosition;
		vEntityPosition = XMLoadFloat4(&vPos);
		fDistance = XMVector4Length(XMVectorSubtract(vEntityPosition, vPosition)).m128_f32[0];
		fDistance = round(fDistance * 1000) / 1000;
		if (fDistance < 0) {
			m_cCollision = FirstCollision;
		}
	}
}