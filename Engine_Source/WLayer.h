#pragma once

#include "WGameObject.h"

namespace W
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(GameObject* _pGameObj);
		const std::vector<GameObject*> GetGameObjects() { return m_vecGameObject; }
	private:
		std::vector<GameObject*> m_vecGameObject;
	};
}


