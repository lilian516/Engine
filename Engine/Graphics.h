#pragma once

// Link necessary d3d12 libraries.
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
#include "Entity.h"


class Graphics
{
public :
	Graphics();
	void initDirectX();

	ID3D12Device *m_d3dDevice;
	IDXGIFactory4 *m_fDxgiFactory;
};

