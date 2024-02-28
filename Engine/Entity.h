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

#include "d3dx12.h"
#include "Transform.h"

class Component;

using namespace std;
using namespace DirectX;




class Entity
{
private :
	vector<Component*> vComponents;
public :
	Entity();
	void AddComponents(Component* cComponent);
	vector<Component*> GetVectorComponents();
	void SRT();
	virtual void update();
	virtual void render();
};

