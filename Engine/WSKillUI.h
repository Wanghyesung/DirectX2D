#pragma once

#include "WUI.h"
#include "WIconUI.h"
namespace W
{
	class SKillUI : public IconUI
	{
	public:
		SKillUI();
		virtual ~SKillUI();

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


