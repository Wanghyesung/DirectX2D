#pragma once

#include "WComponent.h"
#include "WMesh.h"
#include "WShader.h"

namespace W
{
	//���� ������Ʈ������ mesh shader�� ���ؼ� �׷��� ex : mesh renderer
	//���׸���((shader)vs, ps, texture)
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Mesh* m_pMesh;
		Shader* m_pShader;
	};
}

