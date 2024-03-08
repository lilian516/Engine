// Engine.cpp : Définit le point d'entrée de l'application.
//

#include "framework.h"
#include "Engine.h"
#include "Graphics.h"
#include "Manager.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"
#include "BoxMesh.h"
#include "PyramidMesh.h"
#include "PenMesh.h"
#include "Sprite.h"
#include "Texture.h"
#include "Collider.h"
#include "Camera.h"
#include "ParticleSystem.h"

#define MAX_LOADSTRING 100
#ifdef _DEBUG
#include <crtdbg.h>
#endif

// Variables globales :
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale

// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
#ifdef _DEBUG
    _CrtMemState memStateInit;
    _CrtMemCheckpoint(&memStateInit);
#endif
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Placez le code ici.

    Manager oManager;
    Sprite boxMesh;
    
    
    Shader oShader;
    MeshRenderer oMeshRenderer;
	MeshRenderer oMeshRenderer2;
    Texture oTexture;
    Camera ocCamera;
    
    oManager.m_vMesh.push_back(&boxMesh);
    oManager.m_vShader.push_back(&oShader);
    
    
    
    Entity* oCamera = new Entity();
    oCamera->initEntity();


   /* Entity* oEntity = new Entity();
    oEntity->initEntity();*/

    
    oManager.initManager();
   /* oTexture.loadTextureFromFile("test", L"Texture/image.dds", oManager.m_oGraphics.m_d3dDevice,&oManager.m_oGraphics);
    oTexture.buildSRVDescriptorHeap(oManager.m_oGraphics.m_d3dDevice, "test", &oManager.m_oGraphics);
    oMeshRenderer.buildConstantBuffers(oManager.m_oGraphics.m_d3dDevice, oManager.m_oGraphics.m_dConstantBufferViewHeapDescriptor);
    oMeshRenderer.SetMeshRenderer(oEntity, oManager.m_oGraphics.m_d3dDevice, &oShader, &boxMesh, &oTexture);*/
    
    //oEntity->translate(XMFLOAT4(1.5f, 0, 0, 0));

    ocCamera.initCamera(oCamera, &oManager.m_oGraphics.m_hMainWindow);

    

    //oEntity->addComponents(&oMeshRenderer);


	Entity* oEntity2 = new Entity();
    oEntity2->initEntity();
    ParticleSystem* particle = new ParticleSystem();
    particle->setParticleSystem(oEntity2,10, 100, {0,0,0}, &oShader, &boxMesh);
    particle->setConstantBuffers(oManager.m_oGraphics.m_d3dDevice, oManager.m_oGraphics.m_dConstantBufferViewHeapDescriptor);
    oEntity2->addComponents(particle);

    oCamera->addComponents(&ocCamera);

    //oManager.addEntity(oEntity);
    
    oManager.addEntity(oCamera);
	oManager.addEntity(oEntity2);



    oManager.runWindow(hInstance);
    ////Camera* oCamera = new Camera();
    ////oCamera->initCamera(800,600, oEntity);

    //MeshRenderer* oMeshRenderer = new MeshRenderer();
    //oMeshRenderer->SetMeshRenderer(oEntity, oManager->m_oGraphics->m_d3dDevice);
    //oEntity->AddComponents(oMeshRenderer);



    //// Initialise les chaînes globales
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_ENGINE, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);

    //// Effectue l'initialisation de l'application :
    //if (!InitInstance (hInstance, nCmdShow))
    //{
    //    return FALSE;
    //}

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ENGINE));

    //MSG msg;
    //
    //// Boucle de messages principale :
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //    
    //    oManager->mainLoop();
    //    
    //    
    //}

    //return (int) msg.wParam;
#ifdef _DEBUG
    _CrtMemState memStateEnd, memStateDiff;
    _CrtMemCheckpoint(&memStateEnd);
    if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
    {
        MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
    }
#endif 
}

