#pragma once

#include <DirectXMath.h>

using namespace DirectX;

struct Transform
{
	//-- SCALING --//
	XMFLOAT3 m_vScaling;
	XMFLOAT4X4 m_mScaling;

	//-- ROTATION --//
	XMFLOAT3 m_vDirection;
	XMFLOAT3 m_vRight;
	XMFLOAT3 m_vUp;

	XMFLOAT4 m_qRotation;
	XMFLOAT4X4 m_mRotation;

	//-- POSITION --//
	XMFLOAT3 m_vPosition;
	XMFLOAT4X4 m_mPosition;

	//-- TRANSFORM MATRIX --//
	bool m_bUpdate;
	XMFLOAT4X4 m_mTransform;

	//-- FUNCTION --//
	Transform();
	~Transform();

	void Identify();
	void Rotate(float pitch, float roll, float yaw);
	void Scale(XMFLOAT3 ratio);
	void SetPosition(float x, float y, float z);
	void UpdateTransform();
};

