#pragma once

#include <DirectXMath.h>


using namespace DirectX;

struct Transform
{
	//-- SCALING --//
	XMFLOAT4 m_vScaling;
	XMFLOAT4X4 m_mScaling;

	//-- ROTATION --//
	XMFLOAT4 m_vDirection;
	XMFLOAT4 m_vRight;
	XMFLOAT4 m_vUp;

	XMFLOAT4 m_qRotation;
	XMFLOAT4X4 m_mRotation;

	//-- POSITION --//
	XMFLOAT4 m_vPosition;
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
	void translation(XMFLOAT4 vDirection);
	void updateTransform();
};

