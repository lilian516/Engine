#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>

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

private:
	HRESULT m_hHresult;

	ID3DBlob* m_bVertexShader;
	ID3DBlob* m_bPixelShader;

	ID3D12RootSignature* m_d3dRootSignature;
	D3D12_ROOT_SIGNATURE_DESC m_d3dRootSignatureDescriptor;

	ID3D12PipelineState* m_d3dPipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC m_d3dPipelineStateObjectDescriptor;
protected:


};

