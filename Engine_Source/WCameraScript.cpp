#include "WCameraScript.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WTime.h"
#include "WInput.h"

//여기서 오브젝트 로직
namespace W
{
	CameraScript::CameraScript()
	{

	}
	CameraScript::~CameraScript()
	{

	}
	void CameraScript::Update()
	{
		Transform* pTr = GetOwner()->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();
		if (Input::GetKey(eKeyCode::W))
		{
			vPos.z += 5.0f * Time::DeltaTime();
			pTr->SetPosition(vPos);
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			vPos.z -= 5.0f * Time::DeltaTime();
			pTr->SetPosition(vPos);
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			vPos.x -= 5.0f * Time::DeltaTime();
			pTr->SetPosition(vPos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			vPos.x += 5.0f * Time::DeltaTime();
			pTr->SetPosition(vPos);
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			vPos.y -= 5.0f * Time::DeltaTime();
			pTr->SetPosition(vPos);
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			vPos.y += 5.0f * Time::DeltaTime();
			pTr->SetPosition(vPos);
		}

	}
}