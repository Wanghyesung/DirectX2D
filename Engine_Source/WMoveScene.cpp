#include "WMoveScene.h"
#include "WShader.h"
#include "WMeshRenderer.h"
#include "WMesh.h"
#include "WResources.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WInput.h"
#include "WSceneManger.h"

namespace W
{
	MoveScene::MoveScene()
	{
		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"Move1Tex", L"..\\Resources\\Texture\\background\\move1.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"Move1Mater", pNPCMater);
	}
	MoveScene::~MoveScene()
	{

	}
	void MoveScene::Initialize()
	{
		CreateBackground();

		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void MoveScene::Update()
	{
		Scene::Update();
	}
	void MoveScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MoveScene::Render()
	{
		Scene::Render();
	}
	void MoveScene::OnEnter()
	{
	}
	void MoveScene::OnExit()
	{
	}
	void MoveScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"Move1Mater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.f * 10.f, 1.f * 10.f, 1.f);
	}
}