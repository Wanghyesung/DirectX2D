#pragma once
#include "WIconUI.h"
//hlsl ������� (�۷ι�)
// ���������� ����ϴ� ���÷�, ������۸� #include �췯���Ϸ� �߰�����
// �׸��带 ���� ���������ؼ� ���� �������� �׸���
// ����κ� discard
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


