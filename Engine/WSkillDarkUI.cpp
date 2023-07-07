#include "WSkillDarkUI.h"
#include "WInput.h"
namespace W
{
	SkillDarkUI::SkillDarkUI()
	{
		//cool
		std::shared_ptr<Texture> pSKillUI =
			Resources::Load<Texture>(L"SKillDarkUI2", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\dark\\2.png");
		//down
		pSKillUI = Resources::Load<Texture>(L"SKillDarkUI1", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\dark\\1.png");
		//default
		pSKillUI = Resources::Load<Texture>(L"SKillDarkUI0", L"..\\Resources\\Texture\\UI\\SkillUI\\1\\dark\\0.png");

		std::shared_ptr<Material> pSKillMater = std::make_shared<Material>();
		pSKillMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillMater->SetTexture(pSKillUI);
		Resources::Insert(L"SKillDarkUI", pSKillMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillMater);
	}
	SkillDarkUI::~SkillDarkUI()
	{

	}
	void SkillDarkUI::Initialize()
	{

	}
	void SkillDarkUI::Update()
	{
		SKill::Update();
	}
	void SkillDarkUI::LateUpdate()
	{
		SKill::LateUpdate();
	}
	void SkillDarkUI::Render()
	{
		SKill::Render();
	}
	void SkillDarkUI::MouseOn()
	{
		SKill::MouseOn();
	}
	void SkillDarkUI::MouseLbtnDown()
	{
		SKill::MouseLbtnDown();
	}
	void SkillDarkUI::MouseLbtnUp()
	{
		SKill::MouseLbtnUp();
	}
	void SkillDarkUI::MouseLbtnClicked()
	{

	}
}