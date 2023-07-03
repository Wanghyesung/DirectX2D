#include "WHP.h"

namespace W
{
	HP::HP()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"HPTex", L"..\\Resources\\Texture\\UI\\Interface\\HP.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"HPMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	HP::~HP()
	{

	}
	void HP::Initialize()
	{
	}
	void HP::Update()
	{
		UI::Update();
	}
	void HP::LateUpdate()
	{
		UI::LateUpdate();
	}
	void HP::Render()
	{
		UI::Render();
	}
	void HP::MouseOn()
	{
	}
	void HP::MouseLbtnDown()
	{
	}
	void HP::MouseLbtnUp()
	{
	}
	void HP::MouseLbtnClicked()
	{
	}
}