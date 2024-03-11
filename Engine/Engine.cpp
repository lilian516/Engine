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
    BoxMesh test;
    
   
    MeshRenderer oMeshRenderer;
    MeshRenderer oMeshRenderer2;
    Texture oTexture;
    oManager.m_vMesh.push_back(&test);
    
    oManager.initManager();

    oManager.m_oGraphics.createCam();
    oManager.m_vEntity.push_back(oManager.m_oGraphics.m_oCamEntity);
    
    oTexture.loadTextureFromFile("test", L"Texture/image.dds", oManager.m_oGraphics.m_d3dDevice,&oManager.m_oGraphics);
    oTexture.buildSRVDescriptorHeap(oManager.m_oGraphics.m_d3dDevice, "test", &oManager.m_oGraphics);
    
    //oEntity->translate(XMFLOAT4(1.5f, 0, 0, 0));


    Entity* oEntity2 = new Entity();
    oEntity2->initEntity();

    oMeshRenderer2.SetMeshRenderer(oEntity2, oManager.m_oGraphics.m_d3dDevice, &test, &oTexture);

    oEntity2->addComponents(&oMeshRenderer2);

    

    oManager.addEntity(oEntity2);
    oManager.runWindow(hInstance);



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

