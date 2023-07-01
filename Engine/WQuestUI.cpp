#include "WQuestUI.h"

namespace W
{
	QuestUI::QuestUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"questTex0", L"..\\Resources\\Texture\\UI\\Interface\\questBt_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"questMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	QuestUI::~QuestUI()
	{
	}
	void QuestUI::Initialize()
	{
	}
	void QuestUI::Update()
	{
		UI::Update();
	}
	void QuestUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void QuestUI::Render()
	{
		UI::Render();
	}
	void QuestUI::MouseOn()
	{
	}
	void QuestUI::MouseLbtnDown()
	{
	}
	void QuestUI::MouseLbtnUp()
	{
	}
	void QuestUI::MouseLbtnClicked()
	{
	}
}