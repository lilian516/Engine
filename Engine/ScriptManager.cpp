#include "ScriptManager.h"

ScriptManager::ScriptManager(){

}



void ScriptManager::update() {
	if (oStateGame == menu) {
		m_oScript1->update();
	}
	else if (oStateGame == game) {
		m_oScript2->update();
	}
}

void ScriptManager::updateState() {
	switch (oStateGame) {
	case menu:
		oStateGame = game;
		break;
	case game:
		oStateGame = menu;
		break;
	}
}


ScriptManager::~ScriptManager() {
	delete m_oScript1;
	delete m_oScript2;
}