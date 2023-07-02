#pragma once

#include "WItemUI.h"

namespace W
{
	class AlixirUI : public ItemUI
	{
	public:
		AlixirUI();
		virtual ~AlixirUI();

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


