#include "WMP.h"

namespace W
{
	MP::MP()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"MPTex", L"..\\Resources\\Texture\\UI\\Interface\\MP.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"MPMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	MP::~MP()
	{

	}
	void MP::Initialize()
	{

	}
	void MP::Update()
	{
		UI::Update();
	}
	void MP::LateUpdate()
	{
		UI::LateUpdate();
	}
	void MP::Render()
	{
		UI::Render();
	}
	void MP::MouseOn()
	{
	}
	void MP::MouseLbtnDown()
	{
	}
	void MP::MouseLbtnUp()
	{
	}
	void MP::MouseLbtnClicked()
	{
	}
}