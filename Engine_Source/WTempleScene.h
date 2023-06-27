#pragma once
#include "WScene.h"
namespace W
{
	class TempleScene : public Scene
	{
	public:
		TempleScene();
		virtual ~TempleScene();

		virtual void Initialize() override;
		virtual void Update()override ;
		virtual void LateUpdate()override ;
		virtual void Render()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

		virtual void CreateBackground() override;
	private:


	};
}


