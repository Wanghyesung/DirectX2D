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
		static void Release();

		static Scene* GetActiveScene() { return m_pActiveScene; }
		static Scene* LoadScene(std::wstring _strName);

	private:
		static Scene* m_pActiveScene;
		static std::map<std::wstring, Scene*> m_mapScene;
	};
}


