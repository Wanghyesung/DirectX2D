#pragma once

#include "WScene.h"

namespace W
{
	class SceneManger
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

	private:
		static Scene* m_pActiveScene;
	};
}


