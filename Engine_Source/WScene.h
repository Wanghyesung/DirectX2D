#pragma once

#include "WEntity.h"
#include "WLayer.h"
#include "WGraphicDevice_Dx11.h"

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

		virtual void OnEnter();
		virtual void OnExit();
		
		virtual void CreateBackground() {};

		void AddGameObject(eLayerType _eType, GameObject* _pGameObj);

	private:
		std::vector<Layer> m_vecLayer;
	};
}


