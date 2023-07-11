#include "WSkillNumber1.h"
#include "WSKillBox.h"
#include "WSKill.h"
#include "WTransform.h"
#include "WSkillDarkUI.h"
#include "WSkillLuckUI.h"
#include "WSKillStorage.h"
#include "WInput.h"

namespace W
{
	SkillNumber1::SkillNumber1():
		m_bActive(false)
	{
		std::shared_ptr<Texture> pSkillNuber1 =
			Resources::Load<Texture>(L"SKillNuberTex1", L"..\\Resources\\Texture\\UI\\SkillUI\\1.png");

		std::shared_ptr<Texture> pSkillNuber10 =
			Resources::Load<Texture>(L"SKillNuberTex10", L"..\\Resources\\Texture\\UI\\SkillUI\\10.png");

		std::shared_ptr<Material> pSkillNuberMater1 = std::make_shared<Material>();
		pSkillNuberMater1->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSkillNuberMater1->SetTexture(pSkillNuber10);
		Resources::Insert(L"SkillNuberMater1", pSkillNuberMater1);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSkillNuberMater1);
	}
	SkillNumber1::~SkillNumber1()
	{

	}
	void SkillNumber1::Initialize()
	{
		//내 스킬 박스
		SKillBox* pSKillBox1 = new SKillBox();
		pSKillBox1->SetName(L"SKillBox1");
		Transform* pBoxTransform1 = pSKillBox1->GetComponent<Transform>();
		pBoxTransform1->SetPosition(0.25f, -0.8f, -0.01f);
		pBoxTransform1->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox1);

		m_vDarkSkillPosition = Vector3(-0.255f, -0.8f, -0.02f);
		SkillDarkUI* pDarkSkill = new SkillDarkUI();
		pDarkSkill->SetName(L"DarkSkill");
		pDarkSkill->SetSkillNuber(SKillStorage::eSkillNuber::First);
		Transform* pDarkTr = pDarkSkill->GetComponent<Transform>();
		pDarkTr->SetPosition(m_vDarkSkillPosition);
		pDarkTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pDarkSkill);

		//내 스킬 박스
		SKillBox* pSKillBox2 = new SKillBox();
		pSKillBox2->SetName(L"SKillBox2");
		Transform* pBoxTransform2 = pSKillBox2->GetComponent<Transform>();
		pBoxTransform2->SetPosition(1.8f, -0.8f, -0.01f);
		pBoxTransform2->SetScale(0.4f * 3.5f, 0.1f * 3.5f, 0.f); //4 : 1
		AddChildUI(pSKillBox2);

		m_vLuckSkillPosition = Vector3(1.28f, -0.8f, -0.02f);
		SkillLuckUI* pLuckSKill = new SkillLuckUI();
		pLuckSKill->SetName(L"LuckSkill");
		pLuckSKill->SetSkillNuber(SKillStorage::eSkillNuber::First);
		Transform* pLuckTr = pLuckSKill->GetComponent<Transform>();
		pLuckTr->SetPosition(m_vLuckSkillPosition);
		pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
		AddChildUI(pLuckSKill);
	}
	void SkillNumber1::Update()
	{
		if (!m_bActive)
			GameObject::Update();
		else
			UI::Update();
	}
	void SkillNumber1::LateUpdate()
	{
		if (!m_bActive)
		{
			//마우스만 체크
			MouseOnCheck();
			GameObject::LateUpdate();
		}
		else
			UI::LateUpdate();
	}
	void SkillNumber1::Render()
	{
		if (!m_bActive)
			GameObject::Render();
		else
			UI::Render();
	}
	void SkillNumber1::MouseOn()
	{
		
	}
	void SkillNumber1::MouseLbtnDown()
	{
		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"SkillNuberMater1");
		if (m_bActive)
		{
			m_bActive = false;
			pMater->SetTexture(Resources::Find<Texture>(L"SKillNuberTex10"));
		}
		else
		{
			m_bActive = true;
			pMater->SetTexture(Resources::Find<Texture>(L"SKillNuberTex1"));
		}
	}
	void SkillNumber1::MouseLbtnUp()
	{
		
	}
	void SkillNumber1::MouseLbtnClicked()
	{
		
	}

	SKill* SkillNumber1::CreateClone(SKill* _pSkill)
	{
		if (dynamic_cast<SkillDarkUI*>(_pSkill))
		{
			SkillDarkUI* pDarkSkill = new SkillDarkUI();
			pDarkSkill->SetName(L"DarkSkill");
			pDarkSkill->SetSkillNuber(SKillStorage::eSkillNuber::First);
			pDarkSkill->SetClone(true);
			pDarkSkill->SetOwner(_pSkill);
			Transform* pDarkTr = pDarkSkill->GetComponent<Transform>();
			pDarkTr->SetPosition(m_vDarkSkillPosition);
			pDarkTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pDarkSkill);
			return pDarkSkill;
		}
		else if(dynamic_cast<SkillLuckUI*>(_pSkill))
		{
			SkillLuckUI* pLuckSkill = new SkillLuckUI();
			pLuckSkill->SetName(L"DarkSkill");
			pLuckSkill->SetSkillNuber(SKillStorage::eSkillNuber::First);
			pLuckSkill->SetClone(true);
			pLuckSkill->SetOwner(_pSkill);
			Transform* pLuckTr = pLuckSkill->GetComponent<Transform>();
			pLuckTr->SetPosition(m_vLuckSkillPosition);
			pLuckTr->SetScale(0.1f * 3.3f, 0.1f * 3.3f, 0.f); //1 : 1
			AddChildUI(pLuckSkill);
			return pLuckSkill;
		}
		
	}
	
}