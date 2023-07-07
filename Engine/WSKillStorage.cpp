#include "WSKillStorage.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSkillNumber1.h"

namespace W
{
	SKillStorage::SKillStorage():
		m_bRenderOn(false),
		m_bTargetOn(false),
		m_vUIStartPosition(Vector2::One),
		m_vUIEndPosition(Vector2::One),
		m_vUIDiffPosition(Vector2::One)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"SkillUITex", L"..\\Resources\\Texture\\UI\\SkillUI\\SkillUI.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"SkillUIMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	SKillStorage::~SKillStorage()
	{

	}
	void SKillStorage::Initialize()
	{
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, -0.25f);
		pTransform->SetScale(0.881f * 3.8f, 1.f * 3.8f, 0.f); //0.881 : 1


#pragma region SKillNuber
		//스킬 숫자
		SkillNumber1* SKillNumber = new SkillNumber1();
		Transform* pSkillNumberTr = SKillNumber->GetComponent<Transform>();
		pSkillNumberTr->SetPosition(-1.1f, 1.54f, -0.01f);
		pSkillNumberTr->SetScale(0.5f * 0.51f, 0.4f * 0.51f, 0.f); //5 : 4
		AddChildUI(SKillNumber);
		SKillNumber->Initialize();
		
#pragma endregion

	}
	void SKillStorage::Update()
	{
		if (!m_bRenderOn)
			return;
		UI::Update();
	}
	void SKillStorage::LateUpdate()
	{
		if (!m_bRenderOn)
			return;
		UI::LateUpdate();
	}
	void SKillStorage::Render()
	{
		if (!m_bRenderOn)
			return;
		UI::Render();
	}
	void SKillStorage::MouseOn()
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
	void SKillStorage::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void SKillStorage::MouseLbtnUp()
	{
		m_bTargetOn = false;

		//m_vUIEndPosition = Input::GetMousePos();
	}
	void SKillStorage::MouseLbtnClicked()
	{

	}
}