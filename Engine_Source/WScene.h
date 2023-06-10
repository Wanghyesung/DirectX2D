#pragma once

#include "WEntity.h"
#include "WGameObject.h"
#include "WPlayer.h"

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

		bool Check();
		void DeleteObject(GameObject* _pObj);
		void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }

	private:
		std::vector<GameObject*> m_vecGameObject;


		Player* m_pPlayer;
		float m_fCurTime;
		float m_CreateTime;
	};
}


