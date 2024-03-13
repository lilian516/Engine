#pragma once
#include "Component.h"
#include <vector>

class Collider :public Component
{
private:
	enum CollisionState { FirstCollision = 1, Collision = 2, LastCollision = 3, NoCollision = 4 };
	vector<Entity*> m_vColliderEntity;
	Entity* m_eCollidingEntity;
public:
	Collider();
	~Collider();
	void setCollider(Entity* oEntity, vector<Entity*> vColliderEntity);
	void update()override;

	void virtual enterCollision();
	void virtual stayCollision();
	void virtual exitCollision();
	void noCollision();
	Entity* getCollidingEntity();

	CollisionState m_cCollision;
protected:

};

