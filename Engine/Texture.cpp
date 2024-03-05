#include "Texture.h"
#define Assert(x) \
	if (!(x)){ MessageBoxA(0, #x, "Assertion Failed", MB_OK); __debugbreak();}
#define Check(x) \
	if (!(x)){ MessageBoxA(0, #x, "Check Failed", MB_OK); __debugbreak();}

#define CheckSucceded(hresult) \
	Check(SUCCEEDED(hresult))

Texture::Texture() {

}
Texture::~Texture() {
	
}

void Texture::loadTextureFromFile(string name,wstring filename, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	auto createText = std::make_unique<Texture>();
	createText->m_Name = name;
	createText->m_Filename = filename;
	CheckSucceded(DirectX::CreateDDSTextureFromFile12(device,commandList, createText->m_Filename.c_str(), m_rResource, m_rUploadHeap));
}

void Texture::buildSRVDescriptorHeap(ID3D12Device* device, string name, std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures) {
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	CheckSucceded(device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_dSrvHeapDesc)));
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(m_dSrvHeapDesc->GetCPUDescriptorHandleForHeapStart());

	auto CreateText = mTextures[name]->m_rResource;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = CreateText->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = CreateText->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	device->CreateShaderResourceView(CreateText.Get(), &srvDesc, hDescriptor);
}
