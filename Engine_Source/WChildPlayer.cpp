#include "WChildPlayer.h"

#include "WTime.h"
namespace W
{
	ChildPlayer::ChildPlayer():
		m_pOwner(nullptr),
		m_bIsEndMove(false),
		m_fMoveTime(0.f)
	{
	
	}
	ChildPlayer::~ChildPlayer()
	{

	}
	void ChildPlayer::Initialize()
	{
		SetBuffer();
		SetShader("main3");

		SetupState();

		ConstantBuffer();
	}
	void ChildPlayer::Update()
	{
		if (m_pOwner != nullptr)
		{
			if (m_bIsEndMove)
			{
				math::Vector3 vOwnerPos = m_pOwner->GetPos();
				math::Vector3 vPos = GetPos();
				math::Vector2 vDiff = math::Vector2(vOwnerPos.x - vPos.x, vOwnerPos.y - vPos.y);
				math::Vector2 vNor = math::Vector2(vDiff.Length() / vDiff.x, vDiff.Length() / vDiff.y);
				math::Vector2 vForce = vNor * Time::DeltaTime();

				vPos.x += vForce.x;
				vPos.y += vForce.y;

				SetPos(vPos);

				m_pConstantBuffer->SetData(&vPos);
				m_pConstantBuffer->Bind(eShaderStage::VS);
			}
			else
			{
				move();
			}
		}
	}
	void ChildPlayer::LateUpdate()
	{

	}
	void ChildPlayer::Render()
	{
		GetMesh()->BindBuffer();
		GetShader()->Binds();
		graphics::GetDevice()->DrawIndexed(GetMesh()->GetIndexCount(), 0, 0);
	}
	void ChildPlayer::SetBuffer()
	{
		GameObject::SetBuffer();
	}
	void ChildPlayer::SetShader(std::string _strFunName)
	{
		GetShader()->Create(eShaderStage::VS, L"TriangleVS.hlsl", _strFunName);
		GetShader()->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
	}
	void ChildPlayer::ConstantBuffer()
	{
		m_pConstantBuffer = new graphics::ConstantBuffer(eCBType::Transform3);
		m_pConstantBuffer->Create(sizeof(math::Vector4));
	}

	void ChildPlayer::move()
	{
		if (m_fMoveTime >= 1.5f)
		{
			m_bIsEndMove = true;
			return;
		}

		math::Vector3 vPos = GetPos();
		vPos.x += 0.3f * Time::DeltaTime();
		SetPos(vPos);

		m_fMoveTime += Time::DeltaTime();

		m_pConstantBuffer->SetData(&vPos);
		m_pConstantBuffer->Bind(eShaderStage::VS);
	}
}
