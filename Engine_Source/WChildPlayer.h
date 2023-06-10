#pragma once

#include "WGameObject.h"


namespace W
{
	class Scene;

	class ChildPlayer : public GameObject
	{
	public:
		ChildPlayer();
		virtual ~ChildPlayer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void SetBuffer();
		virtual void SetShader(std::string _strFunName);
		virtual void ConstantBuffer();

		bool IsEnd() { return m_bIsEndMove; }

	private:
		GameObject* m_pOwner;//플레이어
		bool m_bIsEndMove;
		float m_fMoveTime;

		graphics::ConstantBuffer* m_pConstantBuffer;
	private:
		void move();

		friend class Scene;
	};
}
