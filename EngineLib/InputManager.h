#pragma once
class InputManager
{
public:

	InputManager();
	void init();
	void update();
	

	~InputManager();

	bool isKey(int i); //Press/Down
	bool isKeyDown(int i);
	bool isKeyUp(int i);

private:
	unsigned char m_cTableau[256];
	enum StateKey {Press,Up,Down,NoPress};

protected:

};

