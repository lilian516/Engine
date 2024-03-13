#pragma once
#include <windows.h>
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <vector>
#include "Transform.h"
#include "AABB.h"

#include "d3dx12.h"


class Component;
class Graphics;


using namespace std;
using namespace DirectX;




class Entity
{
private:

public:

	vector<Component*> m_vComponents;
	Transform m_tTransform;
	AABB m_aBox;

	Entity();
	~Entity();
	void initEntity();
	void addComponents(Component* cComponent);
	
	void move(float fDeltaTime, float fSpeed, XMVECTOR vDir);
	void translate(XMFLOAT3 vDir);
	void rotate(float pitch, float roll, float yaw);
	void scale(XMFLOAT3 ratio);
	Transform& getTransform();
	vector<Component*> getVectorComponents();
	void SRT();
	virtual void update();
	virtual void render(Graphics* oGraphics);
	float m_fRadius = 5.0f;
	float m_fTheta = 1.5f * XM_PI;
	float m_fPhi = XM_PIDIV4;

	template<typename T>
	T* addComponent();
	

};


template<typename T>
T* Entity::addComponent() {
	T* composant = new T();
	m_vComponents.push_back(composant);
	return composant;
}
