#include "WItemUI.h"
#include "WInterfaceUI.h"
#include "WInventory.h"
#include "WInput.h"
#include "WTransform.h"

namespace W
{
	ItemUI::ItemUI():
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::One),
		m_vDragEndPos(Vector2::One),
		m_iItemIndexX(-1),
		m_iItemIndexY(-1),
		m_eParentType(eParentUI::None)
	{
	}
	ItemUI::~ItemUI()
	{
	}
	void ItemUI::Initialize()
	{

	}
	void ItemUI::Update()
	{
		UI::Update();
	}
	void ItemUI::LateUpdate()
	{	
		UI::LateUpdate();
	}
	void ItemUI::Render()
	{
		UI::Render();
	}
	void ItemUI::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}
	}
	void ItemUI::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();

		Transform* pTransform = GetComponent<Transform>();

		Vector3 vPosition = pTransform->GetPosition();
		vPosition.z -= 0.1f;
		pTransform->SetPosition(vPosition);

		m_vStartPos = pTransform->GetPosition();
	}
	void ItemUI::MouseLbtnUp()
	{
		m_bTargetOn = false;

		m_vDragEndPos = Input::GetMousePos();
		//범위 체크

		//여기서 체크
		switch (m_eParentType)
		{
		case W::enums::eParentUI::Interface:
		{
			//changepos_inventory();
		}
			break;
		case W::enums::eParentUI::Inventory:
		{
			changepos_inventory();
		}
			break;
		default:
			break;
		}

		Transform* pTransform = GetComponent<Transform>();

		Vector3 vPosition = pTransform->GetPosition();
		vPosition.z += 0.1f;
		pTransform->SetPosition(vPosition);
	}
	void ItemUI::MouseLbtnClicked()
	{

	}
	void ItemUI::changepos_interface()
	{

	}
	void ItemUI::changepos_inventory()
	{
		UI* pParentUI = GetParentUI();
		Inventory* pInventroy = dynamic_cast<Inventory*>(pParentUI);

		if (pInventroy != nullptr)
		{
			//내 위치
			Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
			//비교할 내 위치
			Vector2 vComparePosition = Vector2(vPosisition.x, vPosisition.y);

			//실패했다면(범위밖에 둠)
			if (!pInventroy->ChangeItemPosition(this, vComparePosition))
			{
				GetComponent<Transform>()->SetPosition(m_vStartPos.x, m_vStartPos.y, vPosisition.z);
			}
		}
	}
}