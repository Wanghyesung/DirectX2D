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
		//��������� ������Ʈ���� �ٸ�����
		//�� ������ ��������� ��� ������Ʈ�鿡�� �Ȱ���
		//����Ǳ� ������ static����
		static Matrix m_mView;
		static Matrix m_projection;

	};
}


