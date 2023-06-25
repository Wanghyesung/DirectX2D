#include "WValleyScene.h"
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
	ValleyScene::ValleyScene()
	{

	}
	ValleyScene::~ValleyScene()
	{

	}
	void ValleyScene::Initialize()
	{
		CreateBackground();


		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void ValleyScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Cave");
		}
	}
	void ValleyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ValleyScene::Render()
	{
		Scene::Render();
	}
	void ValleyScene::OnEnter()
	{

	}
	void ValleyScene::OnExit()
	{

	}
	void ValleyScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"dragonValleyMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(25 * 0.35f,  25.f * 1.f, 1.f);
	}
}
