#include "Graphics.h"
#include "Entity.h"






using namespace DirectX;
using namespace std;

Graphics::Graphics() {

}

void Graphics::initDirectX() {
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		ID3D12Debug *dDebugController;
		D3D12GetDebugInterface(IID_PPV_ARGS(&dDebugController));
		dDebugController->EnableDebugLayer();
	}
#endif

	CreateDXGIFactory1(IID_PPV_ARGS(&m_fDxgiFactory));
	// Try to create hardware device.
	HRESULT hHardwareResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3dDevice));


}
