#include "WSkillNumber1.h"
#include "WSKillBox.h"
#include "WTransform.h"


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
		pBoxTransform1->SetPosition(0.3f, -0.8f, -0.01f);
		pBoxTransform1->SetScale(0.4f * 3.8f, 0.1f * 3.8f, 0.f); //4 : 1
		AddChildUI(pSKillBox1);
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
}