#include "Shader.h"
#define Assert(x) \
	if (!(x)){ MessageBoxA(0, #x, "Assertion Failed", MB_OK); __debugbreak();}
#define Check(x) \
	if (!(x)){ MessageBoxA(0, #x, "Check Failed", MB_OK); __debugbreak();}

#define CheckSucceded(hresult) \
	Check(SUCCEEDED(hresult))
static UINT CalcConstantBufferByteSize(UINT byteSize)
{
	return (byteSize + 255) & ~255;
}
Shader::Shader() {

}

Shader::~Shader() {

}
void Shader::update() {

}

void Shader::initializePipelineState(ID3D12Device* device) {

	m_d3dPipelineStateObjectDescriptor = {};
	
	m_d3dPipelineStateObjectDescriptor.InputLayout = { m_vInputLayout.data(), (UINT)m_vInputLayout.size() };

	m_d3dPipelineStateObjectDescriptor.pRootSignature = m_d3dRootSignature;

	m_d3dPipelineStateObjectDescriptor.VS.pShaderBytecode = m_bVertexShader->GetBufferPointer();
	m_d3dPipelineStateObjectDescriptor.VS.BytecodeLength = m_bVertexShader->GetBufferSize();

	

	m_d3dPipelineStateObjectDescriptor.PS.pShaderBytecode = m_bPixelShader->GetBufferPointer();
	m_d3dPipelineStateObjectDescriptor.PS.BytecodeLength = m_bPixelShader->GetBufferSize();


	m_d3dPipelineStateObjectDescriptor.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	m_d3dPipelineStateObjectDescriptor.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	m_d3dPipelineStateObjectDescriptor.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	m_d3dPipelineStateObjectDescriptor.SampleMask = UINT_MAX;
	m_d3dPipelineStateObjectDescriptor.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	m_d3dPipelineStateObjectDescriptor.NumRenderTargets = 1;
	m_d3dPipelineStateObjectDescriptor.RTVFormats[0] = m_fBackBufferFormat;
	m_d3dPipelineStateObjectDescriptor.SampleDesc.Count = m_b4xMsaaState ? 4 : 1;
	m_d3dPipelineStateObjectDescriptor.SampleDesc.Quality = m_b4xMsaaState ? (m_i4xMsaaQuality - 1) : 0;
	m_d3dPipelineStateObjectDescriptor.DSVFormat = m_fDepthStencilFormat;


	m_hHresult = device->CreateGraphicsPipelineState(&m_d3dPipelineStateObjectDescriptor, IID_PPV_ARGS(&m_d3dPipelineState));
	
	CheckSucceded(m_hHresult);
	
	
}

void Shader::initializeRootSignature(ID3D12Device* device) {

	CD3DX12_ROOT_PARAMETER rootParameters[1];
	rootParameters[0].InitAsConstantBufferView(0);

	CD3DX12_ROOT_SIGNATURE_DESC d3dRootSignatureDescriptor = CD3DX12_ROOT_SIGNATURE_DESC(1, rootParameters, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* signature;
	ID3DBlob* error;

	m_hHresult = D3D12SerializeRootSignature(&d3dRootSignatureDescriptor, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
	CheckSucceded(m_hHresult);
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

	m_vInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}





void Shader::buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap)
{
	m_uObjectCB = std::make_unique<UploadBuffer<ConstantBufferObject>>(device, 1, true);

	//UINT objCBByteSize = CalcConstantBufferByteSize(sizeof(ConstantBufferObject));
	//
	//D3D12_GPU_VIRTUAL_ADDRESS cbAddress = m_uObjectCB->Resource()->GetGPUVirtualAddress();
	//// Offset to the ith object constant buffer in the buffer.
	//int boxCBufIndex = 0;
	//cbAddress += boxCBufIndex * objCBByteSize;
	//
	//D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	//cbvDesc.BufferLocation = cbAddress;
	//cbvDesc.SizeInBytes = CalcConstantBufferByteSize(sizeof(ConstantBufferObject));
	//
	//device->CreateConstantBufferView(
	//	&cbvDesc,
	//	dCbvHeap->GetCPUDescriptorHandleForHeapStart());
}

