#pragma once

#include "WGameObject.h"
namespace W
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void SetBuffer();
		virtual void SetShader(std::string _strFunName);
		virtual void ConstantBuffer();

		void UpScale();
		void AddChild(GameObject* _pObj) { m_vecChildObj.push_back(_pObj); }

	private:
		std::vector<GameObject*> m_vecChildObj;
		float m_fCurTime;
	private:
		void childUpdate();
	};
}


