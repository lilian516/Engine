#pragma once
#include <string>
#include "Entity.h"
#include "DDSTextureLoader.h"
#include <memory>
#include "ObjectConstants.h"
#include "Mesh.h"
#include "Graphics.h"
#include <map>



class Texture
{
public:
	Texture();
	~Texture();
	void loadTextureFromFile(string name,wstring filename, ID3D12Device* device, Graphics* oGraphics);
	void buildSRVDescriptorHeap(ID3D12Device* device, string name, Graphics* oGraphics, std::map<std::string, Texture*> soTexture);

	UINT getDescriptorSize();
	CD3DX12_CPU_DESCRIPTOR_HANDLE getDescriptorHandle();
	CD3DX12_GPU_DESCRIPTOR_HANDLE getGPUDesc();

	std::string m_Name;
	std::wstring m_Filename;

	Microsoft::WRL::ComPtr<ID3D12Resource> m_rResource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_rUploadHeap = nullptr;
	ID3D12DescriptorHeap* HeapDesc = nullptr;

	UINT m_uCbvSrvDescriptorSize;
	CD3DX12_CPU_DESCRIPTOR_HANDLE m_dDescriptorHandle;
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_dDescriptorHandleGPU;
	UINT m_DescriptorIndexCPU = 0; // Suivi de l'index du prochain emplacement disponible dans le heap de descripteurs CPU
	UINT m_DescriptorIndexGPU = 0; // Suivi de l'index du prochain emplacement disponible dans le heap de descripteurs GPU
};

