#pragma once
#include "Windows.h"
#include "Graphics.h"
class InputManager
{
public:

	InputManager();
	void init(Graphics* oGraphic);
	void update();
	

	~InputManager();

	bool isKey(int i); //Press/Down
	bool isKeyDown(int i);
	bool isKeyUp(int i);


	int m_iDeltaX;
	int m_iDeltaY;
	

private:
	unsigned char m_cTableau[256];
	enum StateKey {Press,Up,Down,NoPress};
	POINT m_pLastMousePos;
	POINT m_pMousePos;
	HWND* m_hWindow;
	Graphics* m_oGraphics;
	

protected:

};

