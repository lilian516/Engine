#pragma once
#include "Component.h"
class Camera :public Component
{
public:

	Camera();
	~Camera();
	void initCamera(int windowWidth, int windowHeight);
	void update()override;

private:
	XMFLOAT3 m_fCameraPosition;
	XMFLOAT3 m_fCameraTarget;
	XMFLOAT3 m_fCameraUp;
	XMMATRIX m_mViewMatrix;
	XMMATRIX m_mProjectionMatrix;
	float m_fCameraMoveSpeed;
	POINT m_pMousePose;
protected:

};

