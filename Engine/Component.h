#pragma once
#include "Entity.h"
class Component : public Entity
{
private :
	int m_iId;
public :
	Component();
	void SetComponent(int id);
	int GetId();
};

