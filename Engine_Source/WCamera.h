#pragma once
#include "WComponent.h"
#include "WGraphics.h"

namespace W
{
	class Camera : public Component
	{
	public:
		Camera();
		virtual ~Camera();

	private:
		//월드행렬은 오브젝트마다 다르지만
		//뷰 공간과 투영행렬은 모든 오븍제트들에게 똑같이
		//적용되기 때문에 static으로
		static Matrix m_mView;
		static Matrix m_projection;

	};
}


