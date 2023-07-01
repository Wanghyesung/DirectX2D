#include "WGaugeUI.h"

namespace W
{
	GaugeUI::GaugeUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"gaugeTex0", L"..\\Resources\\Texture\\UI\\Interface\\gauge_back_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"gaugeMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	GaugeUI::~GaugeUI()
	{
	}
	void GaugeUI::Initialize()
	{
	}
	void GaugeUI::Update()
	{
		UI::Update();
	}
	void GaugeUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void GaugeUI::Render()
	{
		UI::Render();
	}
	void GaugeUI::MouseOn()
	{
	}
	void GaugeUI::MouseLbtnDown()
	{
	}
	void GaugeUI::MouseLbtnUp()
	{
	}
	void GaugeUI::MouseLbtnClicked()
	{
	}
}