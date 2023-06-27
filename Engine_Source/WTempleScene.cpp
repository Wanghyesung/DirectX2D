#include "WTempleScene.h"
#include "WResources.h"
#include "WShader.h"
#include "WGameObject.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WMeshRenderer.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WCamera.h"
#include "WCameraScript.h"
namespace W
{
	TempleScene::TempleScene()
	{

	}
	TempleScene::~TempleScene()
	{

	}
	void TempleScene::Initialize()
	{
		CreateBackground();


		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void TempleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Valley2");
		}

	}
	void TempleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TempleScene::Render()
	{
		Scene::Render();
	}

	void TempleScene::OnEnter()
	{

	}
	void TempleScene::OnExit()
	{

	}
	void TempleScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"TempleMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2.5 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.5f * 8.f, 1.f * 8.f, 1.f);
	}
}