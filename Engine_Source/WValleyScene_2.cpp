#include "WValleyScene_2.h"
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
	ValleyScene_2::ValleyScene_2()
	{
	}
	ValleyScene_2::~ValleyScene_2()
	{

	}
	void ValleyScene_2::Initialize()
	{
		CreateBackground();


		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void ValleyScene_2::Update()
	{
		Scene::Update();
		
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Temple2");
		}
	}
	void ValleyScene_2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ValleyScene_2::Render()
	{
		Scene::Render();
	}
	void ValleyScene_2::OnEnter()
	{

	}
	void ValleyScene_2::OnExit()
	{

	}
	void ValleyScene_2::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"dragonValleyMater2"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2 * 8.f, 1.f * 8.f, 1.f);
	}
}