#include "Entity.h"
#include "Component.h"
#include "Graphics.h"
#include "Transform.h"
Entity::Entity() {

}

void Entity::initEntity() {
	//m_tTranform = new Transform();
	m_tTransform.identify();

}

void Entity::AddComponents(Component* cComponent) {
	m_vComponents.push_back(cComponent);
}

vector<Component*> Entity::GetVectorComponents() {
	return m_vComponents;
}

void Entity::SRT() {
	
}

void Entity::update() {
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->update();
	}
	
	
}

void Entity::render(Graphics* oGraphics, XMMATRIX mWorldViewProj) {
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->render(oGraphics, mWorldViewProj);

	}
	temporaire();
}

Transform& Entity::getTransform() {
	return m_tTransform;
}

void Entity::temporaire() {
	//Convert Spherical to Cartesian coordinates.
	float x = m_fRadius * sinf(m_fPhi) * cosf(m_fTheta);
	float z = m_fRadius * sinf(m_fPhi) * sinf(m_fTheta);
	float y = m_fRadius * cosf(m_fPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&m_fView, view);

	XMMATRIX world = XMLoadFloat4x4(&m_tTransform.m_mTransform);
	XMMATRIX proj = XMLoadFloat4x4(&m_fProj);
	m_mWorldViewProj = world * view * proj;

	// Update the constant buffer with the latest worldViewProj matrix.

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.14, static_cast<float>(800) / 600, 1.0f, 1000.0f);
	XMStoreFloat4x4(&m_fProj, P);
}

XMMATRIX Entity::getWorldViewProj() {
	return m_mWorldViewProj;
}