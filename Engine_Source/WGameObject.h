#pragma once

#include "WEntity.h"
#include "WComponent.h"
#include "WConstantBuffer.h"
#include "WMesh.h"
#include "WShader.h"

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

			return nullptr;
		}

		template<typename T>
		T* AddComponent()
		{
			T* comp = new T();
			
			Component* buff =
				dynamic_cast<Component*>(comp);

			if (buff == nullptr)
				return nullptr;

			m_vecComponent.push_back(buff);
			comp->SetOwner(this);

			return comp;
		}

	

	private:
		eState m_eState;
		std::vector<Component*> m_vecComponent;
	};
}


