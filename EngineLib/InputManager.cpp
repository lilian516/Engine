#include "InputManager.h"
#include "Windows.h"

InputManager::InputManager() {

}

void InputManager::init() {
    for (int i = 0; i < 256; i++) {
        m_cTableau[i] = NoPress;
    }
	
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
            switch (i) {
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
    else {
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