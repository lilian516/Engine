#pragma once
class Component
{
private :
	int m_iId;
public :
	Component();
	void setComponent(int iId);
	virtual void update();
	virtual void render();
};

