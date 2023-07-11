#include "WItemUI.h"
#include "WSceneManger.h"
#include "WInterfaceUI.h"
#include "WInventory.h"
#include "WInput.h"
#include "WTransform.h"

namespace W
{
	ItemUI::ItemUI()
	{
		SetIconType(eIconType::Item);
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
		IconUI::MouseOn();
	}
	void ItemUI::MouseLbtnDown()
	{
		IconUI::MouseLbtnDown();
	}
	void ItemUI::MouseLbtnUp()
	{
		IconUI::MouseLbtnUp();

		Transform* pTransform = GetComponent<Transform>();
		Vector3 vStartPos = GetStartPosition();
		//실패하면 원래 있던 자리로
		if (!check_postion())
			pTransform->SetPosition(vStartPos);

	}
	void ItemUI::MouseLbtnClicked()
	{
		IconUI::MouseLbtnClicked();
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
		if (!pInven->IsRender())
			return false;

		Transform* pInvenTr = pInven->GetComponent<Transform>();
		Vector3 vInvenPosition = pInvenTr->GetPosition();

		Vector2 vUIStartPosition = pInven->GetStartPosition();
		Vector2 vUIEndPosition = pInven->GetEndPosition();
		Vector2 vUIDiffPosition = pInven->GetDiffPosition();

		Vector2 vEndPosition = Vector2(vInvenPosition + vUIEndPosition);
		Vector2 vStartPosition = Vector2(vInvenPosition + vUIStartPosition);

		//인벤토리 범위 밖이면
		if (!((vPosition.x <= vEndPosition.x + vUIDiffPosition.x && vPosition.x >= vStartPosition.x - vUIDiffPosition.x) &&
			(vPosition.y >= vEndPosition.y + vUIDiffPosition.y && vPosition.y <= vStartPosition.y - vUIDiffPosition.y)))
			return false;
		else
			if (!changepos_inventory())
				return false;

		return true;
	}

	bool ItemUI::changepos_inventory()
	{
		Inventory* pInventroy = SceneManger::GetUI<Inventory>();

		if (pInventroy != nullptr)
		{
			//내 위치
			Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
			Vector2 vComparePosition = Vector2(vPosisition.x, vPosisition.y);

			bool bSuccess = pInventroy->ChangeItemPosition(this, vComparePosition);
			return bSuccess;
		}
	}

	bool ItemUI::check_interface()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		InterfaceUI* pInter = SceneManger::GetUI<InterfaceUI>();
		Transform* pInterTr = pInter->GetComponent<Transform>();

		Vector2 vUIStartPosition = pInter->GetStartPosition();
		Vector2 vUIEndPosition = pInter->GetEndPosition();
		Vector2 vUIDiffPosition = pInter->GetDiffPosition();

		//인벤토리 범위 밖이면
		if (!((vPosition.x <= vUIEndPosition.x + vUIDiffPosition.x && vPosition.x >= vUIStartPosition.x - vUIDiffPosition.x) &&
			(vPosition.y >= vUIEndPosition.y + vUIDiffPosition.y && vPosition.y <= vUIStartPosition.y - vUIDiffPosition.y)))
			return false;
		else
			if (!changepos_interface())
				return false;

		return true;
	}

	bool ItemUI::changepos_interface()
	{
		InterfaceUI* pInterface = SceneManger::GetUI<InterfaceUI>();

		if (pInterface != nullptr)
		{
			//내 위치
			Vector3 vPosisition = GetComponent<Transform>()->GetPosition();
			//비교할 내 위치
			Vector2 vComparePosition = Vector2(vPosisition.x, vPosisition.y);

			bool bSuccess = pInterface->ChangeItemPosition(this, vComparePosition);
			return bSuccess;
		}

		return false;
	}

}


