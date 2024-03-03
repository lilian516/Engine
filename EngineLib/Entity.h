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
	void addComponent(Component* cComponent);
	Transform& getTransform();
	vector<Component*> GetVectorComponents();
	void SRT();
	virtual void update();
	virtual void render(Graphics* oGraphics);
	
};