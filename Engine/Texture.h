#pragma once
#include <string>
#include "Entity.h"
#include "DDSTextureLoader.h"
#include <unordered_map>
#include <memory>
#include "ObjectConstants.h"
#include "Mesh.h"



class Texture
{
public:
	Texture();
	~Texture();
	void loadTextureFromFile(string name,wstring filename, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	void buildSRVDescriptorHeap(ID3D12Device* device, string name);

	ID3D12DescriptorHeap* getDescriptorHeap();
	UINT getDescriptorSize();
	CD3DX12_CPU_DESCRIPTOR_HANDLE getDescriptorHandle();

	std::string m_Name;
	std::wstring m_Filename;
	std::unordered_map < std::string, Texture*> m_sTextures;

	Microsoft::WRL::ComPtr<ID3D12Resource> m_rResource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_rUploadHeap = nullptr;
	ID3D12DescriptorHeap* m_dSrvHeapDesc = nullptr;

	UINT m_uCbvSrvDescriptorSize;
	CD3DX12_CPU_DESCRIPTOR_HANDLE m_dDescriptorHandle;
};

