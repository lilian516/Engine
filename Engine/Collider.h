#pragma once
#include "Component.h"
#include <vector>

class Collider :public Component
{
private:
	enum CollisionState { FirstCollision, Collision, LastCollision, NoCollision };
	vector<Entity*> m_vColliderEntity;
	Entity* m_eCollidingEntity;
public:
	Collider();
	~Collider();
	void setCollider();
	void update()override;

	void enterCollision();
	void stayCollision();
	void exitCollision();
	void noCollision();

	CollisionState m_cCollision;
protected:

};

