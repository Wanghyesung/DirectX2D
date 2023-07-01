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

		template <typename T>
		std::vector<T*> FindObjectsOfType()
		{
			std::vector<T*> vecObjects = {};
			for (Layer& layer : m_vecLayer)
			{
				const std::vector<GameObject*> vecGameObjects =
					layer.GetGameObjects();
				
				for (GameObject* obj : vecGameObjects)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
						vecObjects.push_back(buff);
				}
			}
			return vecObjects;
		}
		
		Layer& GetLayer(eLayerType _eType) { return m_vecLayer[(UINT)_eType];}

	private:
		std::vector<Layer> m_vecLayer;
	};
}


