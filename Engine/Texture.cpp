#include "Texture.h"
#define Assert(x) \
	if (!(x)){ MessageBoxA(0, #x, "Assertion Failed", MB_OK); __debugbreak();}
#define Check(x) \
	if (!(x)){ MessageBoxA(0, #x, "Check Failed", MB_OK); __debugbreak();}

#define CheckSucceded(hresult) \
	Check(SUCCEEDED(hresult))

Texture::Texture() {}
Texture::~Texture() {
	delete HeapDesc;
}

void Texture::loadTextureFromFile(std::string name, wstring filename, ID3D12Device* device, Graphics* oGraphics) {
	oGraphics->m_cDirectCmdListAlloc->Reset();
	oGraphics->m_cCommandList->Reset(oGraphics->m_cDirectCmdListAlloc, nullptr);
	m_Name = name;
	m_Filename = filename;
	CheckSucceded(DirectX::CreateDDSTextureFromFile12(device, oGraphics->m_cCommandList, m_Filename.c_str(), m_rResource, m_rUploadHeap));
	
}

void Texture::buildSRVDescriptorHeap(ID3D12Device* device, string name, Graphics* oGraphics, std::map<std::string, Texture*> soTexture) {
	m_uCbvSrvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	m_dDescriptorHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(oGraphics->m_dConstantBufferViewHeapDescriptor->GetCPUDescriptorHandleForHeapStart());
	m_dDescriptorHandle.Offset(soTexture.size() - 1, m_uCbvSrvDescriptorSize);
	m_dDescriptorHandleGPU = CD3DX12_GPU_DESCRIPTOR_HANDLE(oGraphics->m_dConstantBufferViewHeapDescriptor->GetGPUDescriptorHandleForHeapStart());
	m_dDescriptorHandleGPU.Offset(soTexture.size() - 1, m_uCbvSrvDescriptorSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = m_rResource->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = m_rResource->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	device->CreateShaderResourceView(m_rResource.Get(), &srvDesc, m_dDescriptorHandle);

	

	oGraphics->m_cCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { oGraphics->m_cCommandList };
	oGraphics->m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	oGraphics->flushCommandQueue();
	m_rUploadHeap.Reset();
}


CD3DX12_GPU_DESCRIPTOR_HANDLE Texture::getGPUDesc() {
	return m_dDescriptorHandleGPU;
}

UINT Texture::getDescriptorSize() {
	return m_uCbvSrvDescriptorSize;
}

CD3DX12_CPU_DESCRIPTOR_HANDLE Texture::getDescriptorHandle() {
	return m_dDescriptorHandle;
}