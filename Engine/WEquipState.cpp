#include "WEquipState.h"
#include "WTransform.h"
#include "WInput.h"
#include "WEquip.h"
namespace W
{
	EquipState::EquipState():
		m_bRenderOn(false),
		m_bTargetOn(false),
		//m_mapItems{},
		m_vDragStartPos(Vector3::One),
		m_vPandantPosition(Vector2::One),
		m_vHatPosition(Vector2::One),
		m_vTopPosition(Vector2::One),
		m_vBottomPosition(Vector2::One),
		m_vShoesPosition(Vector2::One),
		m_vWeaponPosition(Vector2::One)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"EquipUITex", L"..\\Resources\\Texture\\UI\\EquipUI\\EquipUI.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"EquipUIMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	EquipState::~EquipState()
	{
	}
	void EquipState::Initialize()
	{
		//0.634 : 1
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, -0.25f);
		pTransform->SetScale(0.634f * 3.f, 1.f * 3.f, 0.f); //0.518 : 1

		//m_vUIStartPosition = Vector2();
		//m_vUIEndPosition = Vector2();
		m_vUIDiffPosition = Vector2(0.32f,0.32f);

		//장비 위치 초기화
		m_vPandantPosition = Vector2(0.02f, 0.04f);
		m_vHatPosition = Vector2(-0.3f, 1.f);;
		m_vTopPosition = Vector2(-0.3f, 0.04f);;
		m_vBottomPosition = Vector2(-0.3f, -0.28f);;
		m_vShoesPosition = Vector2(0.02f, -0.6f);
		m_vWeaponPosition == Vector2(0.34f, 0.04f);
	}
	void EquipState::Update()
	{
		if (!m_bRenderOn)
			return;

		UI::Update();
	}
	void EquipState::LateUpdate()
	{
		if (!m_bRenderOn)
			return;

		UI::LateUpdate();
	}
	void EquipState::Render()
	{
		if (!m_bRenderOn)
			return;

		UI::Render();
	}
	void EquipState::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			//m_vUIStartPosition += vDiff;
			//m_vUIEndPosition += vDiff;

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}
	}
	void EquipState::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void EquipState::MouseLbtnUp()
	{
		m_bTargetOn = false;
	}
	void EquipState::MouseLbtnClicked()
	{
	}
	void EquipState::SetEquipPosition(IconUI* _pITem)
	{
		_pITem->DeleteParent();
		_pITem->SetParentUIType(eParentUI::EquipState);

		AddChildUI(_pITem,false);
		_pITem->SetItemIndex(-1, -1);

		Equip* pEquip = dynamic_cast<Equip*>(_pITem);
		Equip::EquipType eType = pEquip->GetEquipType();

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		Vector3 vItemPosition = pEquip->GetComponent<Transform>()->GetPosition();

		switch (eType)
		{
		case W::Equip::EquipType::Pandant:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vPandantPosition.x, vPosition.y + m_vPandantPosition.y,vItemPosition.z);
			break;
		case W::Equip::EquipType::Hat:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vHatPosition.x, vPosition.y + m_vHatPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Top:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vTopPosition.x, vPosition.y + m_vTopPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Bottom:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vBottomPosition.x, vPosition.y + m_vBottomPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Shoes:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vShoesPosition.x, vPosition.y + m_vShoesPosition.y, vItemPosition.z);
			break;
		case W::Equip::EquipType::Weapon:
			pEquip->GetComponent<Transform>()->SetPosition(vPosition.x + m_vWeaponPosition.x, vPosition.y + m_vWeaponPosition.y, vItemPosition.z);
			break;
		}

	}
}