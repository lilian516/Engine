// pch.h : Il s'agit d'un fichier d'en-tête précompilé.
// Les fichiers listés ci-dessous sont compilés une seule fois, ce qui améliore les performances de génération des futures builds.
// Cela affecte également les performances d'IntelliSense, notamment la complétion du code et de nombreuses fonctionnalités de navigation du code.
// Toutefois, les fichiers listés ici sont TOUS recompilés si l'un d'entre eux est mis à jour entre les builds.
// N'ajoutez pas de fichiers fréquemment mis à jour ici, car cela annule les gains de performance.

#ifndef PCH_H
#define PCH_H

// ajouter les en-têtes à précompiler ici
#include "framework.h"
#include "d3dx12.h"
#include "DDSTextureLoader.h"
#include "Entity.h"
#include "Graphics.h"
#include "InputManager.h"
#include "Manager.h"
#include "MathHelper.h"
#include "Mesh.h"
#include "Shader.h"
#include "Timer.h"
#include "Transform.h"
#include "UploadBuffer.h"
#include "MeshRenderer.h"
#include "Script.h"
#include "BoxMesh.h"
#include "PyramidMesh.h"
#include "RectangleMesh.h"
#endif //PCH_H 
