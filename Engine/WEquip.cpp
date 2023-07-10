#include "WEquip.h"
#include "WSceneManger.h"
#include "WEquipState.h"
#include "WTransform.h"
#include "WInventory.h"
namespace W
{
	Equip::Equip():
		m_eType(EquipType::None)
	{

	}
	Equip::~Equip()
	{

	}
	void Equip::Initialize()
	{

	}
	void Equip::Update()
	{
		IconUI::Update();
	}
	void Equip::LateUpdate()
	{
		IconUI::LateUpdate();
	}
	void Equip::Render()
	{
		IconUI::Render();
	}
	void Equip::MouseOn()
	{
		IconUI::MouseOn();
	}
	void Equip::MouseLbtnDown()
	{
		IconUI::MouseLbtnDown();
	}
	void Equip::MouseLbtnUp()
	{
		IconUI::MouseLbtnUp();

		if (changepos_equipstate())
			return;
		else if (changepos_inventory())
			return;

		//�� �����ϸ� ���� �ڸ���
		Vector3 vStartPosition = GetStartPosition();
		GetComponent<Transform>()->SetPosition(vStartPosition);
	}

	void Equip::MouseLbtnClicked()
	{

	}

	bool Equip::changepos_equipstate()
	{
		EquipState* pEquipState = SceneManger::GetUI<EquipState>();
		
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();
		//���� �� �������� ���� ��ġ
		Vector2 vFinalPos;

		Transform* pStateTr = pEquipState->GetComponent<Transform>();
		Vector3 vStatePosition = pStateTr->GetPosition();
		Vector2 vDiffPosition = pEquipState->GetDiffPosition();

		Vector2 vPandantPosition = pEquipState->GetPandantPosition();
		Vector2 vHatPosition = pEquipState->GetHatPosition();
		Vector2 vTopPosition = pEquipState->GetTopPosition();
		Vector2 vBottomPosition = pEquipState->GetBottomPosition();
		Vector2 vShoesPosition = pEquipState->GetShoesPosition();
		Vector2 vWeaponPosition = pEquipState->GetWeaponPosition();

		//��� Ŭ������ �ű��
		switch (m_eType)
		{
		case W::Equip::EquipType::Pandant:
			vFinalPos = vPandantPosition + vStatePosition;
			break;
		case W::Equip::EquipType::Hat:
			vFinalPos = vHatPosition + vStatePosition;
			break;
		case W::Equip::EquipType::Top:
			vFinalPos = vTopPosition + vStatePosition;
			break;
		case W::Equip::EquipType::Bottom:
			vFinalPos = vBottomPosition + vStatePosition;
			break;
		case W::Equip::EquipType::Shoes:
			vFinalPos = vShoesPosition + vStatePosition;
			break;
		case W::Equip::EquipType::Weapon:
			vFinalPos = vWeaponPosition + vStatePosition;
			break;
		}

		//���â ���� ���̸�
		if (!((vPosition.x <= vFinalPos.x + vDiffPosition.x && vPosition.x >= vFinalPos.x - vDiffPosition.x) &&
			(vPosition.y <= vFinalPos.y + vDiffPosition.y && vPosition.y >= vFinalPos.y - vDiffPosition.y)))
			return false;
		else
			pEquipState->SetEquipPosition(this);

		return true;
	}

	bool Equip::changepos_inventory()
	{
		Transform* pTransform = GetComponent<Transform>(); 
		Vector3 vPosition = pTransform->GetPosition();

		Inventory* pInventory = SceneManger::GetUI<Inventory>();
		Transform* pInvenTr = pInventory->GetComponent<Transform>();
		Vector3 vInvenPosition = pInvenTr->GetPosition();

		Vector2 vUIStartPosition = pInventory->GetStartPosition();
		Vector2 vUIEndPosition = pInventory->GetEndPosition();
		Vector2 vUIDiffPosition = pInventory->GetDiffPosition();

		Vector2 vEndPosition = Vector2(vInvenPosition + vUIEndPosition);
		Vector2 vStartPosition = Vector2(vInvenPosition + vUIStartPosition);

		//�κ��丮 ���� ���̸�
		if (!((vPosition.x <= vEndPosition.x + vUIDiffPosition.x && vPosition.x >= vStartPosition.x - vUIDiffPosition.x) &&
			(vPosition.y >= vEndPosition.y + vUIDiffPosition.y && vPosition.y <= vStartPosition.y - vUIDiffPosition.y)))
			return false;
		else
			if (! pInventory->ChangeItemPosition(this, Vector2(vPosition.x, vPosition.y)))
				return false;

		return true;
	}
	
}