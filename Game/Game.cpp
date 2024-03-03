// Game.cpp : Définit le point d'entrée de l'application.
//



#include <iostream>


#include "framework.h"
#include "Game.h"


#include "pch.h"
#pragma comment(lib, "EngineLib.lib")



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

    
    oManager->initManager();
    oMeshRenderer->SetMeshRenderer(oEntity, oManager->m_oGraphics->m_d3dDevice, oShader, oMesh);

    oEntity->AddComponents(oMeshRenderer);

    

    oManager->addEntity(oEntity);
    


    oManager->runWindow(hInstance);


}

