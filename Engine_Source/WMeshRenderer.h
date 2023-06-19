#pragma once

#include "WComponent.h"
#include "WMesh.h"
#include "WShader.h"

namespace W
{
	//렌더 컴포넌트에서는 mesh shader을 통해서 그려줌 ex : mesh renderer
	//메테리얼((shader)vs, ps, texture)
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

