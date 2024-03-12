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
    Texture* oTexture1 = new Texture();
    Shader* oShader = new Shader();
    BoxMesh* oBoxMesh = new BoxMesh();
    MeshRenderer* oMeshRenderer = new MeshRenderer();
    oManager->m_vTexture.push_back(oTexture1);
    oManager->m_vMesh.push_back(oBoxMesh);
    oManager->m_vShader.push_back(oShader);
    oManager->m_vMeshRenderer.push_back(oMeshRenderer);
    
  
    //Entity* oEntity = new Entity();
    //oEntity->initEntity();
    //oEntity->m_tTransform.translation(XMFLOAT4(1.5f,0,0,0));
    //oEntity->m_tTransform.updateTransform();
    //
    ////oMeshRenderer->buildConstantBuffers(oManager->m_oGraphics->m_d3dDevice, oManager->m_oGraphics->m_dConstantBufferViewHeapDescriptor);
    oManager->initManager();
    oTexture1->loadTextureFromFile("test", L"Texture/image.dds", oManager->m_oGraphics->m_d3dDevice, oManager->m_oGraphics);
    oTexture1->buildSRVDescriptorHeap(oManager->m_oGraphics->m_d3dDevice, "test",oManager->m_oGraphics);
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
    oEntity4->getTransform().rotate(0,0, XM_PI);
    oEntity4->getTransform().updateTransform();

    oMeshRenderer->SetMeshRenderer(oEntity4, oManager->m_oGraphics->m_d3dDevice, oShader, oBoxMesh, oTexture1);
    oEntity4->AddComponents(oMeshRenderer);

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


