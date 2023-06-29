#pragma once

#include "WEntity.h"
#include "WComponent.h"
#include "WScript.h"
#include "WMaterial.h"
#include "WMeshRenderer.h"

namespace W
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : m_vecComponent)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Component* script : m_vecScript)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}


			return nullptr;
		}

		template<typename T>
		T* AddComponent()
		{
			T* comp = new T();
			
			Component* buff =
				dynamic_cast<Component*>(comp);

			Script* script =
				dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				m_vecComponent.push_back(buff);
			else
				m_vecScript.push_back(script);

			comp->SetOwner(this);

			return comp;
		}

		void SetState(eState _eState) { m_eState = _eState; }

	private:
		eState m_eState;
		std::vector<Component*> m_vecComponent;
		std::vector<Script*> m_vecScript;
	};
}


