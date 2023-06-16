#pragma once

#include "WComponent.h"
#include "WMesh.h"
#include "WShader.h"

namespace W
{
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

