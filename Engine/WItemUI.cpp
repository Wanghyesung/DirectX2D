#include "WItemUI.h"
#include "WSceneManger.h"
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
		m_eParentType(eParentUI::None),
		m_ePrevParentType(eParentUI::None)
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
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		//�����ϸ� ���� �ִ� �ڸ���
		if(!check_postion())
			pTransform->SetPosition(m_vStartPos.x, m_vStartPos.y, vPosition.z);

		vPosition = pTransform->GetPosition();
		vPosition.z = m_vStartPos.z;
		pTransform->SetPosition(vPosition);

	}
	void ItemUI::MouseLbtnClicked()
	{

	}

	bool ItemUI::check_postion()
	{
		if (check_inventory())
			return true;
		
		else if (check_interface())
			return true;

		return false;
	}
	

	bool ItemUI::check_inventory()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		Inventory* pInven = SceneManger::GetUI<Inventory>();
		Transform* pInvenTr = pInven->GetComponent<Transform>();
		Vector3 vInvenPosition = pInvenTr->GetPosition();

		Vector2 vUIStartPosition = pInven->GetStartPosition();
		Vector2 vUIEndPosition = pInven->GetEndPosition();
		Vector2 vUIDiffPosition = pInven->GetDiffPosition();

		Vector2 vEndPosition = Vector2(vInvenPosition + vUIEndPosition);
		Vector2 vStartPosition = Vector2(vInvenPosition + vUIStartPosition);

		//�κ��丮 ���� ���̸�
		if (vPosition.x >= vEndPosition.x + vUIDiffPosition.x || vPosition.x <= vStartPosition.x - vUIDiffPosition.x ||
			vPosition.y <= vEndPosition.y + vUIDiffPosition.y || vPosition.y >= vStartPosition.y - vUIDiffPosition.y)
			return false;
		else
			changepos_inventory();

		return true;
	}

	void ItemUI::changepos_inventory()
	{
		Inventory* pInventroy = SceneManger::GetUI<Inventory>();

		if (pInventroy != nullptr)
		{
			//�� ��ġ
			Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
			//���� �� ��ġ
			Vector2 vComparePosition = Vector2(vPosisition.x, vPosisition.y);

			pInventroy->ChangeItemPosition(this, vComparePosition);

			//�ٸ� UI���� �Դٸ� ���� �θ� UI ����

			if (m_eParentType != eParentUI::Inventory)
			{
				DeleteParent();
				pInventroy->CheckItemPosition(this);
			}

			//�ٸ� �����۰� �ڸ��� �Ȱ��ٸ�
			ItemUI* pSameItem = pInventroy->GetItemSamePos(this);
			if (pSameItem == nullptr)
				return;

			switch (m_ePrevParentType)
			{
			case W::enums::eParentUI::Interface:
			{
				Vector3 vPosition = pSameItem->GetComponent<Transform>()->GetPosition();
				pSameItem->changepos_interface();
				//SceneManger::GetUI<Inventory>()->ChangeItemPosition(pSameItem, Vector2(vPosition.x, vPosition.y));
			}
			break;
			}
		}
	}

	bool ItemUI::check_interface()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		InterfaceUI* pInter = SceneManger::GetUI<InterfaceUI>();
		Transform* pInterTr = pInter->GetComponent<Transform>();
		Vector3 vInterPosition = pInterTr->GetPosition();

		Vector2 vUIStartPosition = pInter->GetStartPosition();
		Vector2 vUIEndPosition = pInter->GetEndPosition();
		Vector2 vUIDiffPosition = pInter->GetDiffPosition();

		//�κ��丮 ���� ���̸�
		if (vPosition.x >= vUIEndPosition.x + vUIDiffPosition.x || vPosition.x <= vUIStartPosition.x - vUIDiffPosition.x ||
			vPosition.y <= vUIEndPosition.y + vUIDiffPosition.y || vPosition.y >= vUIStartPosition.y - vUIDiffPosition.y)
			return false;
		else
			changepos_interface();

		return true;
	}

	void ItemUI::changepos_interface()
	{
		InterfaceUI* pInterface = SceneManger::GetUI<InterfaceUI>();

		if (pInterface != nullptr)
		{
			//�� ��ġ
			Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
			//���� �� ��ġ
			Vector2 vComparePosition = Vector2(vPosisition.x, vPosisition.y);

			//���⼭ ��ġ�� �ٲٰ�
			pInterface->ChangeItemPosition(this, vComparePosition);

			if (m_eParentType != eParentUI::Interface)
			{
				DeleteParent();
				pInterface->CheckItemPosition(this);

				//���� ��ġ�� 2���� 

				ItemUI* pSameItem = pInterface->GetItemSamePos(this);
				if (pSameItem == nullptr)
					return;

				switch (m_ePrevParentType)
				{
				case W::enums::eParentUI::Inventory:
				{
					Vector3 vPosition = pSameItem->GetComponent<Transform>()->GetPosition();
					pSameItem->changepos_inventory();
				}
					break;
				}

			}

		}
	}

	void ItemUI::DeleteParent()
	{
		switch (m_eParentType)
		{
		case W::enums::eParentUI::Interface:
		{
			UI* pParentUI = GetParentUI();
			InterfaceUI* pInter=  dynamic_cast<InterfaceUI*>(pParentUI);
			pInter->DeleteItem(this);
			pInter->DeleteChildUI(this);
		}
			break;
		case W::enums::eParentUI::Inventory:
		{
			UI* pParentUI = GetParentUI();
			Inventory* pInven = dynamic_cast<Inventory*>(pParentUI);
			pInven->DeleteItem(this);
			pInven->DeleteChildUI(this);
		}
			break;
		default:
			break;
		}
	}

}


