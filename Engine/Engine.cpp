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

#define MAX_LOADSTRING 100

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
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Placez le code ici.

    Manager* oManager = new Manager();
    Mesh* oMesh = new Mesh();
    Shader* oShader = new Shader();
   
    MeshRenderer* oMeshRenderer = new MeshRenderer();
    oManager->m_vMesh.push_back(oMesh);
    
    oManager->m_vShader.push_back(oShader);
    oManager->m_vMeshRenderer.push_back(oMeshRenderer);
    
  
    Entity* oEntity = new Entity();
    oEntity->initEntity();
    
    //oMeshRenderer->buildConstantBuffers(oManager->m_oGraphics->m_d3dDevice, oManager->m_oGraphics->m_dConstantBufferViewHeapDescriptor);
    oManager->initManager();
    oMeshRenderer->SetMeshRenderer(oEntity, oManager->m_oGraphics->m_d3dDevice, oShader, oMesh);
    
    oEntity->AddComponents(oMeshRenderer);

   /* Entity* oEntity2 = new Entity();
    oEntity2->initEntity();
    MeshRenderer* oMeshRenderer2 = new MeshRenderer();
    oMeshRenderer2->SetMeshRenderer(oEntity2, oManager->m_oGraphics->m_d3dDevice, oShader, oMesh2);
    oEntity2->AddComponents(oMeshRenderer2);*/
    
    oManager->addEntity(oEntity);
    //oManager->addEntity(oEntity2);
    
    
    oManager->runWindow(hInstance);
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
}


