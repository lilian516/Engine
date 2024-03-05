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
	Texture();
	~Texture();
	void loadTextureFromFile(string name,wstring filename, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	void buildSRVDescriptorHeap(ID3D12Device* device, string name, std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures);

	std::string m_Name;
	std::wstring m_Filename;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_rResource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_rUploadHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_dSrvHeapDesc = nullptr;
};

