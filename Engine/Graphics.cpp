#include "Graphics.h"
#include "Entity.h"
#include <d3d12.h>
#include "MeshRenderer.h"
#include <vector>
#include <iostream>
#include <string>

#include "Shader.h"
#include "Mesh.h"
#include "Manager.h"
#include "Texture.h"
#include "FrameResource.h"


using Microsoft::WRL::ComPtr;


using namespace DirectX;
using namespace std;

#ifndef ReleaseCom
#define ReleaseCom(x) { if(x){ x->Release(); x = 0; } }
#endif

Graphics::Graphics() {

	m_d3dDevice = nullptr;
	m_fDxgiFactory = nullptr;
	m_fFence = nullptr;
	m_cCommandQueue = nullptr;

	m_cDirectCmdListAlloc = nullptr;
	m_cCommandList = nullptr;
	m_cSwapChain = nullptr;
	m_dRtvHeap = nullptr;
	m_dDsvHeap = nullptr;
	m_rDepthStencilBuffer = nullptr;
}

bool Graphics::initGraphics(Manager* oManager) {
	if (initMainWindow() == false) {
		return false;
	}
	if (initDirectX() == false) {
		return false;
	}
	Entity* oCamera = new Entity();
	oCamera->initEntity();

	m_ocCamera.initCamera(oCamera, &m_hMainWindow);
	oCamera->addComponents(&m_ocCamera);
	onResize();
	m_cCommandList->Reset(m_cDirectCmdListAlloc, nullptr);
	createHeapDescriptor();



	for (int i = 0; i < oManager->m_vMesh.size(); i++) {
		oManager->m_vMesh[i]->buildGeometry(m_d3dDevice, m_cCommandList);
	}



	m_cCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { m_cCommandList };
	m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	flushCommandQueue();

	return true;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;



	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


bool Graphics::initMainWindow()
{

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MainWnd";



	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, m_iClientWidth, m_iClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	m_hMainWindow = CreateWindow(L"MainWnd", m_wMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hAppInst, 0);
	if (!m_hMainWindow)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWindow, SW_SHOW);
	UpdateWindow(m_hMainWindow);

	return true;
}


bool Graphics::initDirectX() {
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		ID3D12Debug* dDebugController;
		D3D12GetDebugInterface(IID_PPV_ARGS(&dDebugController));
		dDebugController->EnableDebugLayer();
	}
#endif

CreateDXGIFactory1(IID_PPV_ARGS(&m_fDxgiFactory));
// Try to create hardware device.
HRESULT hHardwareResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3dDevice));

if (FAILED(hHardwareResult))
{
	IDXGIAdapter* aWarpAdapter;
	m_fDxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&aWarpAdapter));

	if (FAILED(D3D12CreateDevice(aWarpAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3dDevice)))) {
		deleteDirectX();
		return false;

	}
}

m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fFence));


m_iRtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
m_iDsvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
m_iCbvSrvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS dQualityLevels;
dQualityLevels.Format = m_fBackBufferFormat;
dQualityLevels.SampleCount = 4;
dQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
dQualityLevels.NumQualityLevels = 0;
m_d3dDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &dQualityLevels, sizeof(dQualityLevels));
m_i4xMsaaQuality = dQualityLevels.NumQualityLevels;
assert(m_i4xMsaaQuality > 0 && "Unexpected MSAA quality level.");

#ifdef _DEBUG
logAdapters();
#endif

createCommandListQueue();
createSwapChain();
createRtvAndDsvDescriptorHeaps();

return true;
}

void Graphics::createCommandListQueue() {
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_cCommandQueue));

	m_d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cDirectCmdListAlloc));

	m_d3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cDirectCmdListAlloc, nullptr, IID_PPV_ARGS(&m_cCommandList));


	//Commencez dans un ?tat ferm?. C'est parce que la premi?re fois que nous faisons r?f?rence
	// ? la liste des commandes, nous allons la r?initialiser, et elle doit ?tre ferm?e avant
	// appelant Reset.
	m_cCommandList->Close();
}

void Graphics::createSwapChain() {
	// Release the previous swapchain we will be recreating.
	m_cSwapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC sSwapChainDescription;
	sSwapChainDescription.BufferDesc.Width = m_iClientWidth;
	sSwapChainDescription.BufferDesc.Height = m_iClientHeight;
	sSwapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
	sSwapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	sSwapChainDescription.BufferDesc.Format = m_fBackBufferFormat;
	sSwapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sSwapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sSwapChainDescription.SampleDesc.Count = m_b4xMsaaState ? 4 : 1;
	sSwapChainDescription.SampleDesc.Quality = m_b4xMsaaState ? (m_i4xMsaaQuality - 1) : 0;
	sSwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sSwapChainDescription.BufferCount = m_sSwapChainBufferCount;
	sSwapChainDescription.OutputWindow = m_hMainWindow;
	sSwapChainDescription.Windowed = true;
	sSwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sSwapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// Note: La cha?ne d'?change utilise la file d'attente pour effectuer le vidage.
	m_fDxgiFactory->CreateSwapChain(m_cCommandQueue, &sSwapChainDescription, &m_cSwapChain);
	//note pour plus tard peut etre probl?me avec throwiffailed
}

void Graphics::createHeapDescriptor() {
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 100;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	HRESULT m_hHresult = m_d3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&m_dConstantBufferViewHeapDescriptor));
}

void Graphics::createRtvAndDsvDescriptorHeaps() {
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = m_sSwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	m_d3dDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_dRtvHeap));
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	m_d3dDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dDsvHeap));
}

void Graphics::onResize() {
	assert(m_d3dDevice);
	assert(m_cSwapChain);
	assert(m_cDirectCmdListAlloc);

	// Flush before changing any resources.
	flushCommandQueue();

	m_cCommandList->Reset(m_cDirectCmdListAlloc, nullptr);

	// Release the previous resources we will be recreating.
	for (int i = 0; i < m_sSwapChainBufferCount; ++i)
		m_cSwapChainBuffer[i].Reset();
	m_rDepthStencilBuffer.Reset();

	// Resize the swap chain.
	m_cSwapChain->ResizeBuffers(
		m_sSwapChainBufferCount,
		m_iClientWidth, m_iClientHeight,
		m_fBackBufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

	m_iCurrBackBuffer = 0;
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_dRtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < m_sSwapChainBufferCount; i++)
	{
		m_cSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_cSwapChainBuffer[i]));
		m_d3dDevice->CreateRenderTargetView(m_cSwapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, m_iRtvDescriptorSize);
	}

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = m_iClientWidth;
	depthStencilDesc.Height = m_iClientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;

	// Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
	// the depth buffer.  Therefore, because we need to create two views to the same resource:
	//   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	//   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
	// we need to create the depth buffer resource with a typeless format.  
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	depthStencilDesc.SampleDesc.Count = m_b4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_b4xMsaaState ? (m_i4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = m_fDepthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;
	CD3DX12_HEAP_PROPERTIES cHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
	m_d3dDevice->CreateCommittedResource(&cHeapProperties, D3D12_HEAP_FLAG_NONE, &depthStencilDesc, D3D12_RESOURCE_STATE_COMMON, &optClear, IID_PPV_ARGS(&m_rDepthStencilBuffer));

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = m_fDepthStencilFormat;
	dsvDesc.Texture2D.MipSlice = 0;
	m_d3dDevice->CreateDepthStencilView(m_rDepthStencilBuffer.Get(), &dsvDesc, depthStencilView());

	// Transition the resource from its initial state to be used as a depth buffer.

	CD3DX12_RESOURCE_BARRIER cTransitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_rDepthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE
	);
	m_cCommandList->ResourceBarrier(1, &cTransitionBarrier);

	// Execute the resize commands.
	m_cCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { m_cCommandList };
	m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete.
	flushCommandQueue();

	// Update the viewport transform to cover the client area.
	m_vScreenViewport.TopLeftX = 0;
	m_vScreenViewport.TopLeftY = 0;
	m_vScreenViewport.Width = static_cast<float>(m_iClientWidth);
	m_vScreenViewport.Height = static_cast<float>(m_iClientHeight);
	m_vScreenViewport.MinDepth = 0.0f;
	m_vScreenViewport.MaxDepth = 1.0f;

	m_rScissorRect = { 0, 0, m_iClientWidth, m_iClientHeight };

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.14, aspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&m_fProj, P);

}

float Graphics::aspectRatio()const
{
	return static_cast<float>(m_iClientWidth) / m_iClientHeight;
}



void Graphics::flushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	m_iCurrentFence++;

	// Add an instruction to the command queue to set a new fence point.  Because we 
	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
	// processing all the commands prior to this Signal().
	m_cCommandQueue->Signal(m_fFence, m_iCurrentFence);

	// Wait until the GPU has completed commands up to this fence point.
	if (m_fFence->GetCompletedValue() < m_iCurrentFence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);

		// Fire event when GPU hits current fence.  
		m_fFence->SetEventOnCompletion(m_iCurrentFence, eventHandle);

		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}


void Graphics::update(Manager* oManager) {

	////Convert Spherical to Cartesian coordinates.
	//float x = m_fRadius * sinf(m_fPhi) * cosf(m_fTheta);
	//float z = m_fRadius * sinf(m_fPhi) * sinf(m_fTheta);
	//float y = m_fRadius * cosf(m_fPhi);

	////// Build the view matrix.
	//XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	//XMVECTOR target = XMVectorZero();
	//XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	//XMStoreFloat4x4(&m_fView, view);

	//XMMATRIX world = XMLoadFloat4x4(&m_fWorld);
	//XMMATRIX proj = XMLoadFloat4x4(&m_fProj);
	//XMMATRIX worldViewProj = world * view * proj;

	////// Update the constant buffer with the latest worldViewProj matrix.
	//ObjectConstants objConstants;
	//XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));

	//for (int i = 0; i < oManager->m_vEntity.size(); i++) {
	//	for (int j = 0; j < oManager->m_vEntity[i]->m_vComponents.size(); j++) {
	//		if (MeshRenderer* meshRenderer = dynamic_cast<MeshRenderer*>(oManager->m_vEntity[i]->m_vComponents[j])) {
	//			meshRenderer->m_uObjectCB->CopyData(0, objConstants);
	//		}

	//	}
	//}

		//oManager->m_vShader[i]->m_uObjectCB->CopyData(0, objConstants);

	for (int i = 0; i < oManager->m_vEntity.size(); i++) {
		oManager->m_vEntity[i]->update();
	}
	onResize();


}

void Graphics::render(Manager* oManager) {
	


	m_cDirectCmdListAlloc->Reset();

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory. m_oShader->m_d3dPipelineState
	m_cCommandList->Reset(m_cDirectCmdListAlloc, nullptr);


	// Set the viewport and scissor rect.  This needs to be reset whenever the command list is reset.
	m_cCommandList->RSSetViewports(1, &m_vScreenViewport);
	m_cCommandList->RSSetScissorRects(1, &m_rScissorRect);



	// Indicate a state transition on the resource usage.
	CD3DX12_RESOURCE_BARRIER rIntermediate = CD3DX12_RESOURCE_BARRIER::Transition(currentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	m_cCommandList->ResourceBarrier(1, &rIntermediate);

	// Clear the back buffer and depth buffer.

	m_cCommandList->ClearRenderTargetView(currentBackBufferView(), m_vColor, 0, nullptr);
	m_cCommandList->ClearDepthStencilView(depthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);



	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBBView = currentBackBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE DSview = depthStencilView();
	m_cCommandList->OMSetRenderTargets(1, &CurrentBBView, true, &DSview);


	//on dessinne ici le cube
	ID3D12DescriptorHeap* descriptorHeaps[] = { m_dConstantBufferViewHeapDescriptor };
	m_cCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);


	// PER OBJECT
	for (int i = 0; i < oManager->m_vEntity.size(); i++) {
		oManager->m_vEntity[i]->render(this);

	}


	/*Entity* oEntity2 = new Entity();
	MeshRenderer* oMeshRenderer = new MeshRenderer();
	oMeshRenderer->SetMeshRenderer(oEntity2, m_d3dDevice, m_oShader, m_oMesh);
	m_cCommandList->SetGraphicsRootSignature(m_oShader->m_d3dRootSignature);
	oMeshRenderer->render(this);*/
	/*m_cCommandList->SetPipelineState(m_oShader->m_d3dPipelineState);

	D3D12_VERTEX_BUFFER_VIEW meshVertexBufferView = m_oMesh->m_mMesh.VertexBufferView();
	m_cCommandList->IASetVertexBuffers(0, 1, &meshVertexBufferView);
	D3D12_INDEX_BUFFER_VIEW meshIndexBufferView = m_oMesh->m_mMesh.IndexBufferView();
	m_cCommandList->IASetIndexBuffer(&meshIndexBufferView);
	m_cCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_cCommandList->SetGraphicsRootConstantBufferView(0, m_oShader->m_uObjectCB->Resource()->GetGPUVirtualAddress());


	m_cCommandList->DrawIndexedInstanced(m_oMesh->m_mMesh.indices.size(),1,0,0,0);*/
	// PER OBJECT



	// Indicate a state transition on the resource usage.
	CD3DX12_RESOURCE_BARRIER rValue = CD3DX12_RESOURCE_BARRIER::Transition(currentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_cCommandList->ResourceBarrier(1, &rValue);

	// Done recording commands.
	m_cCommandList->Close();

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { m_cCommandList };
	m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// swap the back and front buffers
	m_cSwapChain->Present(0, 0);
	m_iCurrBackBuffer = (m_iCurrBackBuffer + 1) % m_sSwapChainBufferCount;

	// Wait until frame commands are complete.  This waiting is inefficient and is
	// done for simplicity.  Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	flushCommandQueue();
}


D3D12_CPU_DESCRIPTOR_HANDLE Graphics::currentBackBufferView()const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		m_dRtvHeap->GetCPUDescriptorHandleForHeapStart(),
		m_iCurrBackBuffer,
		m_iRtvDescriptorSize);
}

ID3D12Resource* Graphics::currentBackBuffer()const
{
	return m_cSwapChainBuffer[m_iCurrBackBuffer].Get();
}

D3D12_CPU_DESCRIPTOR_HANDLE Graphics::depthStencilView()const
{
	return m_dDsvHeap->GetCPUDescriptorHandleForHeapStart();
}


void Graphics::logAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	while (m_fDxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		std::wstring text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.push_back(adapter);

		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		logAdapterOutputs(adapterList[i]);
		ReleaseCom(adapterList[i]);
	}
}

void Graphics::logAdapterOutputs(IDXGIAdapter* adapter)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		logOutputDisplayModes(output, m_fBackBufferFormat);

		ReleaseCom(output);

		++i;
	}
}

void Graphics::logOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	std::vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::wstring text =
			L"Width = " + std::to_wstring(x.Width) + L" " +
			L"Height = " + std::to_wstring(x.Height) + L" " +
			L"Refresh = " + std::to_wstring(n) + L"/" + std::to_wstring(d) +
			L"\n";

		::OutputDebugString(text.c_str());
	}
}

void Graphics::updateCam(Entity* oEntity) {

}

bool Graphics::deleteDirectX() {
	if (m_rDepthStencilBuffer)
	{
		m_rDepthStencilBuffer->Release();
		m_rDepthStencilBuffer = nullptr;
	}
	if (m_dDsvHeap)
	{
		m_dDsvHeap->Release();
		m_dDsvHeap = nullptr;
	}
	if (m_dRtvHeap)
	{
		m_dRtvHeap->Release();
		m_dRtvHeap = nullptr;
	}
	if (m_cCommandList)
	{
		m_cCommandList->Release();
		m_cCommandList = nullptr;
	}
	if (m_cDirectCmdListAlloc)
	{
		m_cDirectCmdListAlloc->Release();
		m_cDirectCmdListAlloc = nullptr;
	}
	if (m_cCommandQueue)
	{
		m_cCommandQueue->Release();
		m_cCommandQueue = nullptr;
	}
	if (m_fFence)
	{
		m_fFence->Release();
		m_fFence = nullptr;
	}
	if (m_d3dDevice)
	{
		m_d3dDevice->Release();
		m_d3dDevice = nullptr;
	}
	if (m_fDxgiFactory)
	{
		m_fDxgiFactory->Release();
		m_fDxgiFactory = nullptr;
	}
	return true;
}