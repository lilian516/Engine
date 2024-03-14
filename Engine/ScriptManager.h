#pragma once
#include "Component.h"
#include "Script.h"

class ScriptManager : public Script
{
public:
	ScriptManager();
	~ScriptManager();
	template<typename S1, typename S2, typename S3>
	void setScriptManager(Entity* oEntity, S1* oScript1, S2* oScript2, S3* oScript3);
	void update()override;
	void updateState();


	enum stateGame{menu,game,loose};
	stateGame oStateGame;
	Script* m_oScript1;
	Script* m_oScript2;
	Script* m_oScript3;
};

template<typename S1, typename S2, typename S3>
void ScriptManager::setScriptManager(Entity* oEntity, S1* oScript1, S2* oScript2, S3* oScript3) {
	initComponent(5, oEntity);
	oStateGame = menu;
	m_oScript1 = oScript1;
	m_oScript2 = oScript2;
	m_oScript3 = oScript3;
}
