#pragma once
#include <string>
#include "d3dx12.h"
#include "ObjectConstants.h"

struct Material
{
	Material();
	std::string Name;
	int MatCBIndex = -1;

	int DiffuseSrvHeapIndex = -1;

	int NormalSrvHeapIndex = -1;

	int NumFramesDirty = 0;

	DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
	float Roughness = .25f;
	DirectX::XMFLOAT4X4 MatTransform = Identity4x4();
};