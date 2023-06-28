#include "WCaveScene.h"
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
	CaveScene::CaveScene()
	{

	}
	CaveScene::~CaveScene()
	{

	}
	void CaveScene::Initialize()
	{
		CreateBackground();

		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void CaveScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Temple");
		}
	}
	void CaveScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void CaveScene::Render()
	{
		Scene::Render();
	}
	void CaveScene::OnEnter()
	{

	}
	void CaveScene::OnExit()
	{

	}
	void CaveScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"WoodCaveMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//14::10
		pBackGround->GetComponent<Transform>()->SetScale(14.f * 1.f, 10.f * 1.f, 1.f);
		
	}
}