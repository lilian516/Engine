#pragma once
#include "Component.h"
#include "Script.h"

class ScriptManager : public Component
{
public:
	ScriptManager();
	template<typename S1, typename S2>
	void setScriptManager(Entity* oEntity, S1* oScript1, S2* oScript2);
	void update()override;
	void updateState();


	enum stateGame{menu,game};
	stateGame oStateGame;
	Script* m_oScript1;
	Script* m_oScript2;
};

template<typename S1, typename S2>
void ScriptManager::setScriptManager(Entity* oEntity, S1* oScript1, S2* oScript2) {
	initComponent(5, oEntity);
	oStateGame = menu;
	m_oScript1 = oScript1;
	m_oScript2 = oScript2;
}
