#pragma once
#include "WItemUI.h"

namespace W
{
	class HorntailItem : public ItemUI
	{
	public:
		HorntailItem();
		virtual ~HorntailItem();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	private:
	};
}

