#include "InputManager.h"
#include "Windows.h"

InputManager::InputManager() {
    m_iDeltaX = 0;
    m_iDeltaY = 0;
}

void InputManager::init(HWND *hWindow) {
    for (int i = 0; i < 256; i++) {
        m_cTableau[i] = NoPress;
    }

    m_hWindow = hWindow;
	
}

void InputManager::update() {
	for (int i = 0; i < 256; i++) {
		
        if ( GetAsyncKeyState(i) < 0 )
        {
            switch (m_cTableau[i]) {
                case Press:
                    m_cTableau[i] = Press;
                    break;
                case Up:
                    m_cTableau[i] = Down;
                    break;
                case Down:
                    m_cTableau[i] = Press;
                    break;
                case NoPress:
                    m_cTableau[i] = Down;
                    break;
            }
               
            
            
        }
        else
        {
            switch (m_cTableau[i]) {
                case Press:
                    m_cTableau[i] = Up;
                    break;
                case Up:
                    m_cTableau[i] = NoPress;
                    break;
                case Down:
                    m_cTableau[i] = Up;
                    break;
                case NoPress:
                    m_cTableau[i] = NoPress;
                    break;
                }
        }

        
		
	}


    POINT currentMousePos;
    GetCursorPos(&currentMousePos);
    //ScreenToClient(*m_hWindow, &currentMousePos);
    

    // Calculez les différences de position de la souris entre les cadres
    m_iDeltaX = currentMousePos.x - m_pLastMousePos.x;
    m_iDeltaY = currentMousePos.y - m_pLastMousePos.y;


    m_pLastMousePos = currentMousePos;
    
    //SetCursorPos(400, 300);
    
    //ScreenToClient(*m_hWindow, &m_pLastMousePos);

    
}

bool InputManager::isKey(int i ) {
    if (m_cTableau[i] == Press)
    {
        return true;
    }
    else if (m_cTableau[i] == Down)
    {
        return true;
    }
    else{
        return false;
    }
}
    //Press/Down
bool InputManager::isKeyDown(int i) {
    if (m_cTableau[i] == Down)
    {
        return true;
    }
    else {
        return false;
    }
}


bool InputManager::isKeyUp(int i) {
    if (m_cTableau[i] == Up)
    {
        return true;
    }
    else {
        return false;
    }
}





InputManager::~InputManager() {

}