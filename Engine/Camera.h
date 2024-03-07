#pragma once
#include "Component.h"
#include "ObjectConstants.h"
class Camera :public Component
{
public:

	Camera();
	~Camera();
	void initCamera(Entity *oEntity,HWND* hWnd);
	void updateMatrix();
	void update()override;
	XMFLOAT4X4* getViewMatrix();

private:
	XMFLOAT3 m_fPosition = { 1.0f,0.0f,0.0f };
	float m_yaw;
	float m_pitch;
	float m_fRotationSpeed;

	float m_AspectRatio;
	float m_FovAngleY;
	float m_NearZ;
	float m_FarZ;
	XMFLOAT3 m_forward;
	XMFLOAT4X4 m_mViewMatrix;
	XMFLOAT4X4 m_mProjMatrix = Identity4x4();

	float m_fMouseX;
	float m_fMouseY;

	POINT m_pCenter;
	HWND* m_hWnd;
protected:

};

