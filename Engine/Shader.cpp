#include "Shader.h"
#define Assert(x) \
	if (!(x)){ MessageBoxA(0, #x, "Assertion Failed", MB_OK); __debugbreak();}
#define Check(x) \
	if (!(x)){ MessageBoxA(0, #x, "Check Failed", MB_OK); __debugbreak();}

#define CheckSucceded(hresult) \
	Check(SUCCEEDED(hresult))

Shader::Shader() {

}

Shader::~Shader() {

}

void Shader::initializePipelineState(ID3D12Device* device) {

	m_d3dPipelineStateObjectDescriptor = {};
	m_d3dPipelineStateObjectDescriptor.pRootSignature = m_d3dRootSignature;
	m_d3dPipelineStateObjectDescriptor.VS.pShaderBytecode = m_bVertexShader->GetBufferPointer();
	m_d3dPipelineStateObjectDescriptor.VS.BytecodeLength = m_bVertexShader->GetBufferSize();
	m_d3dPipelineStateObjectDescriptor.PS.pShaderBytecode = m_bPixelShader->GetBufferPointer();
	m_d3dPipelineStateObjectDescriptor.PS.BytecodeLength = m_bPixelShader->GetBufferSize();


	m_hHresult =device->CreateGraphicsPipelineState(&m_d3dPipelineStateObjectDescriptor, IID_PPV_ARGS(&m_d3dPipelineState));
	CheckSucceded(m_hHresult);
}

void Shader::initializeRootSignature(ID3D12Device* device) {

	m_d3dRootSignature = {};
	ID3DBlob* signature;
	ID3DBlob* error;

	D3D12SerializeRootSignature(&m_d3dRootSignatureDescriptor, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
	m_hHresult = device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_d3dRootSignature));
	CheckSucceded(m_hHresult);

	signature->Release();
	if (error) error->Release();

}

HRESULT Shader::compileShader(const WCHAR* filename, const char* entrypoint, const char* profile, ID3DBlob** out_code) {
	ID3DBlob* errors;
	m_hHresult = D3DCompileFromFile(filename, 0, 0, entrypoint, profile, D3DCOMPILE_DEBUG, 0, out_code, &errors);
	CheckSucceded(m_hHresult);

	return m_hHresult;
}

void Shader::initializeShader() {
	m_hHresult = compileShader(L"Shader.hlsl", "vs_main", "vs_5_0", &m_bVertexShader);
	CheckSucceded(m_hHresult);
	m_hHresult = compileShader(L"Shader.hlsl", "ps_main", "ps_5_0", &m_bPixelShader);
	CheckSucceded(m_hHresult);
}