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
#include "framework.h"

using namespace std;


class Manager
{
public :
	Manager();
	void initManager();
	void mainLoop();
	void update();
	void render();
	void addEntity(Entity* oEntity);
	int runWindow(HINSTANCE hInstance);
	Entity* createEntity();
	Shader* createShader();
	Texture* createTexture(std::string name, wstring filename);
	Mesh* createMesh(std::string name);
	
	~Manager();

	Graphics m_oGraphics;
	Timer m_oTimer;
	InputManager m_oInputManager;
	vector<Entity*> m_vCollideEntity;
	vector<Entity*> m_vEntity;
	vector<Shader*> m_vShader;
	vector<Mesh*> m_vMesh;
	vector<Texture*> m_vTexture;
	
	
	
};

