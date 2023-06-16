#pragma once

#include "WEntity.h"
#include "WLayer.h"

namespace W
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(eLayerType _eType, GameObject* _pGameObj);

	private:
		std::vector<Layer> m_vecLayer;
	};
}


