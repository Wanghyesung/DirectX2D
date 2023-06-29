#pragma once

#include "WScene.h"

namespace W
{
	class ValleyScene : public Scene
	{
	public:
		ValleyScene();
		virtual ~ValleyScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

		virtual void CreateBackground() override;

	private:
		void setobject();
	};
}




