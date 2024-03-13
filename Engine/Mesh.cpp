#include "Mesh.h"
#include "Graphics.h"
#include <stdexcept>

D3D12_VERTEX_BUFFER_VIEW MeshData::VertexBufferView()const
{
	D3D12_VERTEX_BUFFER_VIEW vbv;
	vbv.BufferLocation = vertexBufferGPU->GetGPUVirtualAddress();
	vbv.StrideInBytes = vertexByteStride;
	vbv.SizeInBytes = vertexByteSize;

	return vbv;
}

D3D12_INDEX_BUFFER_VIEW MeshData::IndexBufferView()const
{
	D3D12_INDEX_BUFFER_VIEW ibv;
	ibv.BufferLocation = indexBufferGPU->GetGPUVirtualAddress();
	ibv.Format = indexFormat;
	ibv.SizeInBytes = indexBufferByteSize;

	return ibv;
}

Mesh::Mesh() {

}

Mesh::~Mesh() {
	
}

void Mesh::update() {

}

void Mesh::init(ID3D12Device* device) {

}

void Mesh::uploadMeshToBuffers(MeshData mesh, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {

	
	const UINT vbByteSize = (UINT)m_mMesh.vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)m_mMesh.indices.size() * sizeof(std::uint16_t);

	/*ThrowIfFailed(D3DCreateBlob(vbByteSize, &m_mBoxGeo->VertexBufferCPU));
	CopyMemory(m_mBoxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &m_mBoxGeo->IndexBufferCPU));
	CopyMemory(m_mBoxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);*/

	m_mMesh.vertexBufferGPU = CreateDefaultBuffer(device,
		commandList, m_mMesh.vertices.data(), vbByteSize, m_mMesh.vertexBuffer);

	m_mMesh.indexBufferGPU = CreateDefaultBuffer(device,
		commandList, m_mMesh.indices.data(), ibByteSize, m_mMesh.indexBuffer);

	m_mMesh.vertexByteStride= sizeof(Vertex);
	m_mMesh.vertexByteSize = vbByteSize;
	m_mMesh.indexFormat = DXGI_FORMAT_R16_UINT;
	m_mMesh.indexBufferByteSize = ibByteSize;


}

ID3D12Resource* Mesh::CreateDefaultBuffer(ID3D12Device* device,ID3D12GraphicsCommandList* cmdList,const void* initData,UINT64 byteSize,ID3D12Resource* &uploadBuffer)
{
	ID3D12Resource* defaultBuffer;

	// Create the actual default buffer resource.
	CD3DX12_HEAP_PROPERTIES iValue1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC iValue2 = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
	device->CreateCommittedResource(
		&iValue1,
		D3D12_HEAP_FLAG_NONE,
		&iValue2,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&defaultBuffer));

	// In order to copy CPU memory data into our default buffer, we need to create
	// an intermediate upload heap.
	CD3DX12_HEAP_PROPERTIES iValue3 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC iValue4 = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
	device->CreateCommittedResource(
		&iValue3,
		D3D12_HEAP_FLAG_NONE,
		&iValue4,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&uploadBuffer));


	// Describe the data we want to copy into the default buffer.
	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	// Schedule to copy the data to the default buffer resource.  At a high level, the helper function UpdateSubresources
	// will copy the CPU memory into the intermediate upload heap.  Then, using ID3D12CommandList::CopySubresourceRegion,
	// the intermediate upload heap data will be copied to mBuffer.
	CD3DX12_RESOURCE_BARRIER iValue5 = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
	cmdList->ResourceBarrier(1, &iValue5);

	UpdateSubresources<1>(cmdList, defaultBuffer, uploadBuffer, 0, 0, 1, &subResourceData);

	CD3DX12_RESOURCE_BARRIER iValue6 = CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
	cmdList->ResourceBarrier(1, &iValue6);

	// Note: uploadBuffer has to be kept alive after the above function calls because
	// the command list has not been executed yet that performs the actual copy.
	// The caller can Release the uploadBuffer after it knows the copy has been executed.
	return defaultBuffer;
}

void Mesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}