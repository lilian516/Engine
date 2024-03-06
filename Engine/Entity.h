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

#include "d3dx12.h"
#include "ObjectConstants.h"

class Component;
class Graphics;


using namespace std;
using namespace DirectX;




class Entity
{
private :
	
public :
	
	vector<Component*> m_vComponents;
	Transform m_tTransform;
	Entity();
	void initEntity();
	void AddComponents(Component* cComponent);
	Transform& getTransform();
	vector<Component*> GetVectorComponents();
	void SRT();
	virtual void update();
	virtual void render(Graphics* oGraphics, XMFLOAT4X4* mWorldViewProj);

	

	// à enlever en deuxieme
	void temporaire();
	float m_fRadius = 5.0f;
	float m_fTheta = 1.5f * XM_PI;
	float m_fPhi = XM_PIDIV4;
	XMFLOAT4X4 m_fWorld = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	XMFLOAT4X4 m_mWorldViewProj;
	XMFLOAT4X4* getWorldViewProj();
	
	// à enlever en premier
	XMFLOAT4X4 m_fProj = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
};