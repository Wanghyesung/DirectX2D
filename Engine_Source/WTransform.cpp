#include "WTransform.h"
#include "WRenderer.h"
#include "WConstantBuffer.h"
#include "WCamera.h"
namespace W
{
	using namespace W::graphics;

	Transform::Transform():
		Component(eComponentType::Transform),
		m_vPosition(Vector3::Zero),
		m_vRotation(Vector3::Zero),
		m_vScale(Vector3::One)
	{

	}
	Transform::~Transform()
	{

	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::LateUpdate()
	{
		m_vWorld = Matrix::Identity;//傈瘤 青纺

		//农扁 青纺 积己
		Matrix mScale = Matrix::CreateScale(m_vScale);

		Matrix mRotation;
		mRotation = Matrix::CreateRotationX(m_vRotation.x);
		mRotation = Matrix::CreateRotationY(m_vRotation.y);
		mRotation = Matrix::CreateRotationZ(m_vRotation.z);

		Matrix mPosition;
		mPosition.Translation(m_vPosition);

		m_vWorld = mScale * mRotation * mPosition;

		m_vUp = Vector3::TransformNormal(Vector3::Up, mRotation);
		m_vFoward = Vector3::TransformNormal(Vector3::Forward, mRotation);
		m_vRight = Vector3::TransformNormal(Vector3::Right, mRotation);
	}
	void Transform::Render()
	{

	}
	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.m_mWorld = m_vWorld;
		trCB.m_mView = Camera::GetViewMatrix();
		trCB.m_mProjection = Camera::GetProjectionMatrix();

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Transform];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&trCB);
		pConstBuffer->Bind(eShaderStage::VS);
	}
}