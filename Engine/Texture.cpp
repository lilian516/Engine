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

void Texture::loadTextureFromFile(wstring filename, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	auto woodCrateTex = std::make_unique<Texture>();
	woodCrateTex->m_Name = "woodCrateTex";
	woodCrateTex->m_Filename = filename;
	CheckSucceded(DirectX::CreateDDSTextureFromFile12(device,commandList, woodCrateTex->m_Filename.c_str(), m_rResource, m_rUploadHeap));
	mTextures[woodCrateTex->m_Name] = std::move(woodCrateTex);
}

void Texture::buildSRVDescriptorHeap(ID3D12Device* device) {
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	CheckSucceded(device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_dSrvHeapDesc)));
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(m_dSrvHeapDesc->GetCPUDescriptorHandleForHeapStart());

	auto CrateTex = mTextures["CrateTex"]->m_rResource;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = CrateTex->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = CrateTex->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	device->CreateShaderResourceView(CrateTex.Get(), &srvDesc, hDescriptor);
}

void Texture::BuildMaterials()
{
	auto woodCrate = std::make_unique<Material>();
	woodCrate->Name = "woodCrate";
	woodCrate->MatCBIndex = 0;
	woodCrate->DiffuseSrvHeapIndex = 0;
	woodCrate->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	woodCrate->FresnelR0 = XMFLOAT3(0.05f, 0.05f, 0.05f);
	woodCrate->Roughness = 0.2f;

	mMaterials["woodCrate"] = std::move(woodCrate);
}

void Texture::BuildRenderItems()
{
	auto boxRitem = std::make_unique<RenderItem>();
	boxRitem->ObjCBIndex = 0;
	boxRitem->Mat = mMaterials["woodCrate"].get();
	boxRitem->Geo = mGeometries["boxGeo"].get();
	boxRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	boxRitem->IndexCount = boxRitem->Geo->DrawArgs["box"].IndexCount;
	boxRitem->StartIndexLocation = boxRitem->Geo->DrawArgs["box"].StartIndexLocation;
	boxRitem->BaseVertexLocation = boxRitem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(boxRitem));

	// All the render items are opaque.
	for (auto& e : mAllRitems)
		mOpaqueRitems.push_back(e.get());
}