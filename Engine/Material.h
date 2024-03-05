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

struct MaterialConstants
{
	DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
	float Roughness = 0.25f;

	// Used in texture mapping.
	DirectX::XMFLOAT4X4 MatTransform = Identity4x4();
};

struct PassConstants
{
    DirectX::XMFLOAT4X4 View = Identity4x4();
    DirectX::XMFLOAT4X4 InvView = Identity4x4();
    DirectX::XMFLOAT4X4 Proj = Identity4x4();
    DirectX::XMFLOAT4X4 InvProj = Identity4x4();
    DirectX::XMFLOAT4X4 ViewProj = Identity4x4();
    DirectX::XMFLOAT4X4 InvViewProj = Identity4x4();
    DirectX::XMFLOAT3 EyePosW = { 0.0f, 0.0f, 0.0f };
    float cbPerObjectPad1 = 0.0f;
    DirectX::XMFLOAT2 RenderTargetSize = { 0.0f, 0.0f };
    DirectX::XMFLOAT2 InvRenderTargetSize = { 0.0f, 0.0f };
    float NearZ = 0.0f;
    float FarZ = 0.0f;
    float TotalTime = 0.0f;
    float DeltaTime = 0.0f;

    DirectX::XMFLOAT4 AmbientLight = { 0.0f, 0.0f, 0.0f, 1.0f };

};