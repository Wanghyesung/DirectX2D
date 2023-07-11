#pragma once
#include "WIconUI.h"
//hlsl 헤더파일 (글로벌)
// 공통적으로 사용하는 샘플러, 상수버퍼를 #include 헤러파일로 추가가능
// 그리드를 가장 안쪽으로해서 가장 마지막에 그리게
// 흰색부분 discard
//

namespace W
{
	class ItemUI : public IconUI
	{
	public:
		ItemUI();
		virtual ~ItemUI();
		
		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	
	private:
		bool changepos_interface();
		bool changepos_inventory();

		bool check_postion();
		bool check_inventory();
		bool check_interface();
	};
}


