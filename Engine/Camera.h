#pragma once
#include "Component.h"
class Camera :public Component
{
public:

	Camera();
	~Camera();
	void initCamera(Entity *oEntity);
	void update()override;

private:
	XMFLOAT3 m_fPosition;
	float m_yaw;
	float m_pitch;

	float m_fMoveSpeed;
	float m_fRotationSpeed;

	XMFLOAT4X4 m_mViewMatrix;

	float m_fMouseX;
	float m_fMouseY;
protected:

};

