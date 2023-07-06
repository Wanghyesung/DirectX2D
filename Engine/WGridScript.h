#pragma once

#include <WScript.h>
#include "WCamera.h"

namespace W
{
	class GridScript : public Script
	{
	public:
		GridScript();
		virtual ~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { m_pCamera = camera; }

	private:
		Camera* m_pCamera;

	};
}


