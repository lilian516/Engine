#pragma once
#include "Graphics.h"
#include "Entity.h"
#include "Shader.h"
#include "Mesh.h"
#include "InputManager.h"

#include "Timer.h"
#include <vector>
#include <iostream>

class MeshRenderer;

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
	void runWindow(HINSTANCE hInstance);
	
	~Manager();

	Graphics *m_oGraphics;
	Timer* m_oTimer;
	InputManager *m_oInputManager;
	vector<Entity*> m_vEntity;
	vector<Shader*> m_vShader;
	vector<Mesh*> m_vMesh;
	vector<MeshRenderer*> m_vMeshRenderer;
	Mesh* m_oMesh;
	Shader* m_oShader;
	
};

