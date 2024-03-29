#pragma once
#include "Graphics.h"
#include "Entity.h"
#include "Shader.h"
#include "Mesh.h"
#include "InputManager.h"
#include "MeshRenderer.h"
#include "Timer.h"
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "framework.h"

using namespace std;


class Manager
{
public :
	Manager();
	void initManager();
	void mainLoop(HINSTANCE hInstance);
	void update();
	void render();
	void addEntity(Entity* oEntity);
	
	Entity* createEntity();
	Shader* createShader();
	Texture* createTexture(std::string name, wstring filename);
	void addCollideEntity(Entity* oEntity);
	void deleteEntity(Entity* oEntity);
	
	template<typename T>T* createMesh();
	
	~Manager();

	Graphics m_oGraphics;
	Timer m_oTimer;
	InputManager m_oInputManager;
	vector<Entity*> m_vCollideEntity;
	vector<Entity*> m_vEntity;
	vector<Mesh*> m_vMesh;
	std::map<std::string, Texture*> m_vTexture;
	vector<Shader*> m_vShader;
	
	
	
};

template<typename T>
T* Manager::createMesh() {
	m_oGraphics.m_cCommandList->Reset(m_oGraphics.m_cDirectCmdListAlloc, nullptr);
	T* mesh = new T();
	mesh->buildGeometry(m_oGraphics.m_d3dDevice, m_oGraphics.m_cCommandList);
	m_vMesh.push_back(mesh);

	m_oGraphics.m_cCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { m_oGraphics.m_cCommandList };
	m_oGraphics.m_cCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	m_oGraphics.flushCommandQueue();
	return mesh;
	
}

