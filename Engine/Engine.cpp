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
    BoxMesh boxMesh;
    PyramidMesh pyramidMesh;
    PenMesh penMesh;
    
    Shader oShader;
    
    
    MeshRenderer oMeshRenderer;
    MeshRenderer oMeshRenderer2;
    MeshRenderer oMeshRenderer3;
    oManager.m_vMesh.push_back(&boxMesh);
    oManager.m_vMesh.push_back(&pyramidMesh);
    oManager.m_vMesh.push_back(&penMesh);
    oManager.m_vShader.push_back(&oShader);
    oManager.m_vMeshRenderer.push_back(&oMeshRenderer);
    oManager.m_vMeshRenderer.push_back(&oMeshRenderer2);
    oManager.m_vMeshRenderer.push_back(&oMeshRenderer3);


    Entity* oEntity = new Entity();
    oEntity->initEntity();

    //oMeshRenderer->buildConstantBuffers(oManager->m_oGraphics->m_d3dDevice, oManager->m_oGraphics->m_dConstantBufferViewHeapDescriptor);
    oManager.initManager();
    oMeshRenderer.SetMeshRenderer(oEntity, oManager.m_oGraphics.m_d3dDevice, &oShader, &boxMesh);
    oEntity->translate(XMFLOAT4(1.5f, 0, 0, 0));

    oManager.m_vCollideEntity.push_back(oEntity);
    Collider* collider = new Collider();
    collider->setCollider(oEntity, oManager.m_vCollideEntity);
    oEntity->addComponents(collider);

    oEntity->addComponents(&oMeshRenderer);

    Entity* oEntity2 = new Entity();
    oEntity2->initEntity();

    oMeshRenderer2.SetMeshRenderer(oEntity2, oManager.m_oGraphics.m_d3dDevice, &oShader, &pyramidMesh);
    oEntity2->addComponents(&oMeshRenderer2);
    oEntity2->translate(XMFLOAT4(-1.5f, 0, 0, 0));

    oManager.m_vCollideEntity.push_back(oEntity2);
    Collider* collider2 = new Collider();
    collider2->setCollider(oEntity2, oManager.m_vCollideEntity);
    oEntity->addComponents(collider2);

    Entity* oEntity3 = new Entity();
    oEntity3->initEntity();

    oMeshRenderer3.SetMeshRenderer(oEntity3, oManager.m_oGraphics.m_d3dDevice, &oShader, &penMesh);
    oEntity2->addComponents(&oMeshRenderer3);

    oManager.addEntity(oEntity);
    oManager.addEntity(oEntity2);
    oManager.addEntity(oEntity3);



    //oManager.runWindow(hInstance);
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

