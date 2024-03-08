#pragma once
#include "ObjectConstants.h"
class Component;

class Camera :public Component
{
public:

	Camera();
	~Camera();
	void initCamera(Entity *oEntity, float aspectRatio);
	void updateMatrix();
	void update();
	void change();
	void changePos();
	XMFLOAT4X4* getViewMatrix();
	XMFLOAT4X4* getProjMatrix();

private:
	float m_fRotationSpeed;

	float m_AspectRatio;
	float m_FovAngleY;
	float m_NearZ;
	float m_FarZ;

	XMVECTOR m_vPosition;
	XMVECTOR m_vForward;

	XMMATRIX m_mViewMatrix;
	XMFLOAT4X4 m_mMatrixView = Identity4x4();

	XMMATRIX m_mProjMatrix;
	XMFLOAT4X4 m_mMatrixProj = Identity4x4();

	XMVECTOR m_vUp;
	XMVECTOR m_vTarget;

	Transform* camTransform;
protected:

};

