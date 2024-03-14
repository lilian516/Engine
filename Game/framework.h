// header.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets
//

#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "../x64/debug/Engine.lib")
#else
	#pragma comment(lib, "../x64/release/Engine.lib")
#endif

#include "targetver.h"

#include "../Engine/framework.h"

// Fichiers d'en-tête Windows
//#include <windows.h>
//// Fichiers d'en-tête C RunTime
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
