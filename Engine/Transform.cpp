#include "Transform.h"

Transform::Transform(){}
Transform::~Transform(){}

void Transform::Identify() {
	//-- SCALING --//
	m_vScaling = { 1.f,1.f,1.f };
	m_mScaling = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	//-- ROTATION --//
	m_vDirection = { 0.0f,0.0f,1.0f };
	m_vRight = { 1.0f,0.0f,0.0f };
	m_vUp = { 0.0f,1.0f,0.0f };

	m_qRotation = { 0.0f,0.0f,0.0f,1.0f };
	m_mRotation = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	//-- POSITION --//
	m_vPosition = { 0.0f,0.0f,0.0f };
	m_mPosition = { 
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f 
	};

	//-- TRANSFORM MATRIX --//
	m_bUpdate = false;
	m_mTransform = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

void Transform::Rotate(float pitch, float roll, float yaw) {
	XMVECTOR vQuaternion;

	XMVECTOR vDirection = XMLoadFloat3(&m_vDirection);
	XMVECTOR vRight = XMLoadFloat3(&m_vRight);
	XMVECTOR vUp = XMLoadFloat3(&m_vUp);
	XMVECTOR vQuaternionRotation = XMLoadFloat4(&m_qRotation);

	vQuaternion = XMQuaternionRotationAxis(vDirection, roll);
	vQuaternion *= XMQuaternionRotationAxis(vRight, pitch);
	vQuaternion *= XMQuaternionRotationAxis(vUp, yaw);
	vQuaternionRotation *= vQuaternion;

	XMStoreFloat4(&m_qRotation, vQuaternionRotation);
	

	XMMATRIX mRotation = XMMatrixRotationQuaternion(vQuaternionRotation);
	XMStoreFloat4x4(&m_mRotation, mRotation);

	m_vRight.x = m_mRotation._11;
	m_vRight.y = m_mRotation._12;
	m_vRight.z = m_mRotation._13;
	m_vUp.x = m_mRotation._21;
	m_vUp.y = m_mRotation._22;
	m_vUp.z = m_mRotation._23;
	m_vDirection.x = m_mRotation._31;
	m_vDirection.y = m_mRotation._32;
	m_vDirection.z = m_mRotation._33;

	m_bUpdate = true;
}

void Transform::Scale(XMFLOAT3 ratio) {
	XMVECTOR vRatio = XMLoadFloat3(&ratio);
	XMVECTOR vScale = XMLoadFloat3(&m_vScaling);

	vScale *= vRatio;
	XMStoreFloat3(&m_vScaling, vScale);

	m_mScaling._11 *= m_vScaling.x;
	m_mScaling._22 *= m_vScaling.y;
	m_mScaling._33 *= m_vScaling.z;

	m_bUpdate = true;
}

void Transform::UpdateTransform() {
	if (m_bUpdate) {
		XMMATRIX mRotation = XMLoadFloat4x4(&m_mRotation);
		XMMATRIX mPosition = XMLoadFloat4x4(&m_mPosition);
		XMMATRIX mScaling = XMLoadFloat4x4(&m_mScaling);
		XMMATRIX mTransform = XMLoadFloat4x4(&m_mTransform);

		mTransform = mRotation * mPosition * mScaling;
		XMStoreFloat4x4(&m_mTransform, mTransform);
		m_bUpdate = false;
	}
}

