#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <vector>
#include "Entity.h"
class Shader
{
public:
	Shader();
	~Shader();
	void update();
	void initializePipelineState(ID3D12Device* device);
	void initializeRootSignature(ID3D12Device* device);
	void initializeShader();
	HRESULT compileShader(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code);
	ID3D12PipelineState* m_d3dPipelineState;
	ID3D12RootSignature* m_d3dRootSignature;

private:
	HRESULT m_hHresult;

	std::vector<D3D12_INPUT_ELEMENT_DESC> m_vInputLayout;

	ID3DBlob* m_bVertexShader;
	ID3DBlob* m_bPixelShader;

	
	D3D12_ROOT_SIGNATURE_DESC m_d3dRootSignatureDescriptor;

	
	D3D12_GRAPHICS_PIPELINE_STATE_DESC m_d3dPipelineStateObjectDescriptor;
protected:

	DXGI_FORMAT m_fBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	bool      m_b4xMsaaState = false;
	UINT      m_i4xMsaaQuality = 0;

	DXGI_FORMAT m_fDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
};

