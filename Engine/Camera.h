#pragma once
#include "ObjectConstants.h"
#include "Component.h"
#include <DirectXMath.h>
#include "UploadBuffer.h"

class Camera :public Component
{
public:

	Camera();
	~Camera();
	void initCamera(Entity *oEntity, float aspectRatio, ID3D12Device* device);
	void updateMatrix();
	void update();
	void change();
	void changePos();
	DirectX::XMFLOAT4X4* getProjMatrix();
	UploadBuffer<ObjectConstants> *m_uCamCB;

private:
	float m_fRotationSpeed;

	float m_AspectRatio;
	float m_FovAngleY;
	float m_NearZ;
	float m_FarZ;

	//DirectX::XMVECTOR m_vPosition;
	//DirectX::XMVECTOR m_vForward;

	//DirectX::XMMATRIX m_mViewMatrix;
	//DirectX::XMFLOAT4X4 m_mMatrixView = Identity4x4();

	DirectX::XMMATRIX m_mProjMatrix;
	DirectX::XMFLOAT4X4 m_mMatrixProj = Identity4x4();

	//DirectX::XMVECTOR m_vUp;
	//DirectX::XMVECTOR m_vTarget;

	Transform* camTransform;
protected:

};

