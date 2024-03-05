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
    Shader* oShader = new Shader();
    BoxMesh* oBoxMesh = new BoxMesh();
    PyramidMesh* oPyramidMesh =new PyramidMesh();
    PenMesh* oPenMesh = new PenMesh();
    Sprite* oSprite = new Sprite();
    MeshRenderer* oMeshRenderer = new MeshRenderer();
    MeshRenderer* oMeshRenderer2 = new MeshRenderer();
    MeshRenderer* oMeshRenderer3 = new MeshRenderer();
    MeshRenderer* oMeshRenderer4 = new MeshRenderer();
    oManager->m_vMesh.push_back(oBoxMesh);
    oManager->m_vMesh.push_back(oPyramidMesh);
    oManager->m_vMesh.push_back(oPenMesh);
    oManager->m_vMesh.push_back(oSprite);
    oManager->m_vShader.push_back(oShader);
    oManager->m_vMeshRenderer.push_back(oMeshRenderer);
    oManager->m_vMeshRenderer.push_back(oMeshRenderer2);
    oManager->m_vMeshRenderer.push_back(oMeshRenderer3);
    oManager->m_vMeshRenderer.push_back(oMeshRenderer4);
    
  
    //Entity* oEntity = new Entity();
    //oEntity->initEntity();
    //oEntity->m_tTransform.translation(XMFLOAT4(1.5f,0,0,0));
    //oEntity->m_tTransform.updateTransform();
    //
    ////oMeshRenderer->buildConstantBuffers(oManager->m_oGraphics->m_d3dDevice, oManager->m_oGraphics->m_dConstantBufferViewHeapDescriptor);
    oManager->initManager();
    //oMeshRenderer->SetMeshRenderer(oEntity, oManager->m_oGraphics->m_d3dDevice, oShader, oBoxMesh);
    //
    //oEntity->AddComponents(oMeshRenderer);

    //Entity* oEntity2 = new Entity();
    //oEntity2->initEntity();
    //oEntity2->m_tTransform.translation(XMFLOAT4(-1.5, 0, 0, 0));
    //oEntity2->m_tTransform.updateTransform();

    //oMeshRenderer2->SetMeshRenderer(oEntity2, oManager->m_oGraphics->m_d3dDevice, oShader, oPyramidMesh);
    //oEntity2->AddComponents(oMeshRenderer2);

    //Entity* oEntity3 = new Entity();
    //oEntity3->initEntity();

    //oMeshRenderer3->SetMeshRenderer(oEntity3, oManager->m_oGraphics->m_d3dDevice, oShader, oPenMesh);
    //oEntity2->AddComponents(oMeshRenderer3);
    // 
    
    Entity* oEntity4 = new Entity();
    oEntity4->initEntity();

    oMeshRenderer4->SetMeshRenderer(oEntity4, oManager->m_oGraphics->m_d3dDevice, oShader, oSprite);
    oEntity4->AddComponents(oMeshRenderer4);

    //
    //oManager->addEntity(oEntity);
    //oManager->addEntity(oEntity2);
    //oManager->addEntity(oEntity3);
    oManager->addEntity(oEntity4);

    
    
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


