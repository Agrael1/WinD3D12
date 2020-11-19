#pragma once
#include "Drawable.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ModelException.h"


namespace ver
{
	class Model
	{
	public:
		Model(Graphics& gfx, std::string_view pathString, float scale = 1.0f)
		{
			Assimp::Importer imp;
			const auto* pScene = imp.ReadFile(pathString.data(),
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_ConvertToLeftHanded |
				aiProcess_GenNormals |
				aiProcess_CalcTangentSpace
			);

			if(!pScene) throw ModelException(__LINE__, __FILE__, imp.GetErrorString());
		}
	};
}
