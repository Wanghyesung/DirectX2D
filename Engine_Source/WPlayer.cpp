#include "WPlayer.h"
#include "WInput.h"
#include "WTime.h"
#include "WRenderer.h"
#include "WChildPlayer.h"

namespace W
{
	Player::Player():
		m_vecChildObj{},
		m_fCurTime(0.f)
	{
	}
	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		SetBuffer();
		SetShader("main");

		SetupState();

		ConstantBuffer();
	}
	void Player::Update()
	{
		m_fCurTime += Time::DeltaTime();

		Vector3 m_vPos = GetPos();

		if (Input::GetKey(eKeyCode::RIGHT))
			m_vPos.x += 1.f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::LEFT))
			m_vPos.x -= 1.f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::UP))
			m_vPos.y += 1.f * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::DOWN))
			m_vPos.y -= 1.f * Time::DeltaTime();
			

		SetPos(m_vPos);

		GetConstBuffer()->SetData(&m_vPos);
		GetConstBuffer()->Bind(eShaderStage::VS);
	}
	void Player::LateUpdate()
	{
	}
	void Player::Render()
	{
		GetMesh()->BindBuffer();
		GetShader()->Binds();
		graphics::GetDevice()->DrawIndexed(GetMesh()->GetIndexCount(), 0, 0);
	}
	void Player::SetBuffer()
	{
		GameObject::SetBuffer();
	}
	void Player::SetShader(std::string _strFunName)
	{
		GetShader()->Create(eShaderStage::VS, L"TriangleVS.hlsl", _strFunName);
		GetShader()->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
	}

	void Player::ConstantBuffer()
	{
		GetConstBuffer()->Create(sizeof(math::Vector4));
	}

	void Player::UpScale()
	{
		Vector3 m_vPos = GetPos();
		m_vPos.z += 0.1f;
		SetPos(m_vPos);

		GetConstBuffer()->SetData(&m_vPos);
		GetConstBuffer()->Bind(eShaderStage::VS);
	}
}