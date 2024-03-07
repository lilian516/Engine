#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <vector>
#include "Entity.h"
#include <memory>
#include "Graphics.h"
#include "ObjectConstants.h"
#include "d3d12.h"

#include "UploadBuffer.h"

using namespace std;


class Shader
{
public:
	
	Shader();
	~Shader();
	void init(ID3D12Device* device);
	void update();
	void initializePipelineState(ID3D12Device* device);
	void initializeRootSignature(ID3D12Device* device);
	void buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap);
	void initializeShader();
	vector<CD3DX12_STATIC_SAMPLER_DESC> GetStaticSamplers();
	HRESULT compileShader(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code);
	ID3D12PipelineState* m_d3dPipelineState;
	ID3D12RootSignature* m_d3dRootSignature;
	

private:
	HRESULT m_hHresult;
	std::vector<D3D12_INPUT_ELEMENT_DESC> m_vInputLayout;
	ID3DBlob* m_bVertexShader = nullptr;
	ID3DBlob* m_bPixelShader = nullptr;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC m_d3dPipelineStateObjectDescriptor;
	D3D12_CONSTANT_BUFFER_VIEW_DESC m_bConstantBufferViewDescriptor;
	ID3D12Resource* m_rConstantBuffer = nullptr;
	UINT m_uConstantBufferSize;
	
protected:

	DXGI_FORMAT m_fBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	bool      m_b4xMsaaState = false;
	UINT      m_i4xMsaaQuality = 0;

	DXGI_FORMAT m_fDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
};
