#pragma once

#include <DirectXMath.h>


using namespace DirectX;

struct Transform
{
	//-- SCALING --//
	XMFLOAT3 m_vScaling;
	XMFLOAT4X4 m_mScaling;

	//-- ROTATION --//
	XMFLOAT3 m_vRotation;
	XMFLOAT4 m_vDirection;
	XMFLOAT4 m_vRight;
	XMFLOAT4 m_vUp;

	XMFLOAT3 m_fTarget;

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

	void identify();
	void rotate(float pitch, float roll, float yaw);
	void scale(XMFLOAT3 ratio);
	void translation(XMFLOAT3 vDirection);
	void updateTransform();
	XMVECTOR getForwardVector();
};

