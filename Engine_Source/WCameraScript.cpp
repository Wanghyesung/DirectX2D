#include "WCameraScript.h"
#include "WTransform.h"
#include "WGameObject.h"
#include "WTime.h"


//여기서 오브젝트 로직
namespace W
{
	WCameraScript::WCameraScript()
	{

	}
	WCameraScript::~WCameraScript()
	{

	}
	void WCameraScript::Update()
	{
		Transform* pTr = GetOwner()->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();
		vPos.x += 1.f * Time::DeltaTime();
		pTr->SetPosition(vPos);
	}
}