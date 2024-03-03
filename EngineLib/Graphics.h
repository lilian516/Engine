#pragma once

// Link necessary d3d12 libraries.
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include "Entity.h"
#include <string>



#include "ObjectConstants.h"


class Shader;
class Mesh;
class Manager;


class Graphics
{
public :
	Graphics();
	bool initGraphics(Manager* oManager);
	bool initDirectX();
	bool deleteDirectX();
	void logAdapters();
	void logAdapterOutputs(IDXGIAdapter* adapter);
	void logOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);
	void createCommandListQueue();
	void createSwapChain();
	void createRtvAndDsvDescriptorHeaps();
	void onResize();
	void createHeapDescriptor();
	void flushCommandQueue();
	bool initMainWindow();
	void render(Manager* oManager);
	void update(Manager* oManager);
	float aspectRatio()const;
	D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE currentBackBufferView()const;
	ID3D12Resource* currentBackBuffer()const;
	ID3D12DescriptorHeap* m_dConstantBufferViewHeapDescriptor = nullptr;
	

	ID3D12Device *m_d3dDevice;
	IDXGIFactory4 *m_fDxgiFactory;
	ID3D12Fence *m_fFence;
	UINT m_iRtvDescriptorSize = 0;
	UINT m_iDsvDescriptorSize = 0;
	UINT m_iCbvSrvDescriptorSize = 0;
	DXGI_FORMAT m_fBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	UINT      m_i4xMsaaQuality = 0;
	bool      m_b4xMsaaState = false;
	ID3D12CommandQueue *m_cCommandQueue;
	ID3D12CommandAllocator *m_cDirectCmdListAlloc;
	ID3D12GraphicsCommandList *m_cCommandList;
	IDXGISwapChain *m_cSwapChain;

	static const int m_sSwapChainBufferCount = 2;
	//ID3D12Resource *m_cSwapChainBuffer[m_sSwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> m_cSwapChainBuffer[m_sSwapChainBufferCount];
	HWND      m_hMainWindow = nullptr;
	ID3D12DescriptorHeap *m_dRtvHeap;
	ID3D12DescriptorHeap *m_dDsvHeap;
	int m_iClientWidth = 800;
	int m_iClientHeight = 600;
	UINT64 m_iCurrentFence = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_rDepthStencilBuffer;
	int m_iCurrBackBuffer = 0;
	DXGI_FORMAT m_fDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	D3D12_VIEWPORT m_vScreenViewport;
	D3D12_RECT m_rScissorRect;
	HINSTANCE m_hAppInst = nullptr;
	std::wstring m_wMainWndCaption = L"App Les 4 fantastiques";

	XMVECTORF32 m_vColor = Colors::LightSkyBlue;


	float m_fRadius = 5.0f;
	float m_fTheta = 1.5f * XM_PI;
	float m_fPhi = XM_PIDIV4;

	XMFLOAT4X4 m_fWorld = Identity4x4();
	XMFLOAT4X4 m_fView = Identity4x4();
	XMFLOAT4X4 m_fProj = Identity4x4();
	
	
	

};
