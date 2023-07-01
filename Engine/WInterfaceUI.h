#pragma once
#include "WUI.h"

namespace W
{
	class InterfaceUI : public UI
	{
	public:
		InterfaceUI();
		virtual ~InterfaceUI();


		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
		virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
		virtual void MouseLbtnUp();//UI안에서 땠을 때
		virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

	};

}

