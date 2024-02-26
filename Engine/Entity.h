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

#include "d3dx12.h"


using namespace std;
using namespace DirectX;

struct Transform
{
	XMVECTOR vPosition;
	XMVECTOR vScale;
};


class Entity
{

public :
	Entity();
	Transform tTransform;
};

