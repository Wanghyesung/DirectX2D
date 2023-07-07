#pragma once
#include "WUI.h"

namespace W
{
	class SKill : public UI
	{
	public:
		SKill();
		virtual ~SKill();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

	private:
		bool m_bTargetOn;
		Vector2 m_vDragStartPos;

	};
}


