#include "WSKillBox.h"
namespace W
{
	SKillBox::SKillBox()
	{
		std::shared_ptr<Texture> pSkillBoxTex =
			Resources::Load<Texture>(L"SkillBoxTex", L"..\\Resources\\Texture\\UI\\SkillUI\\SkillBox.png");

		std::shared_ptr<Material> pSKillBoxMater = std::make_shared<Material>();
		pSKillBoxMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pSKillBoxMater->SetTexture(pSkillBoxTex);
		Resources::Insert(L"SkillBoxMater", pSKillBoxMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pSKillBoxMater);

	}
	SKillBox::~SKillBox()
	{

	}
	void SKillBox::Initialize()
	{

	}
	void SKillBox::Update()
	{
		UI::Update();
	}
	void SKillBox::LateUpdate()
	{
		UI::LateUpdate();
	}
	void SKillBox::Render()
	{
		UI::Render();
	}
	void SKillBox::MouseOn()
	{

	}
	void SKillBox::MouseLbtnDown()
	{

	}
	void SKillBox::MouseLbtnUp()
	{

	}
	void SKillBox::MouseLbtnClicked()
	{

	}
}