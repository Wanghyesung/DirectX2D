#pragma once

#include "WResource.h"
#include "WGraphics.h"

#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "..\External\DirectXTex\Include\DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

namespace W::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& _strPath);
		void BindShader(eShaderStage _eStage, UINT _iStartSlot);

	private:
		//scratchImage�����̹����� �������� ����ִ� Ȯ����
		ScratchImage m_Image;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpTexture;//2d�̹���
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cpSRV;//shader������ view
		D3D11_TEXTURE2D_DESC m_tDesc;
	};

	//�ؽ���(uv��ǥ)�� �ȼ��� �ϳ��ϳ� �Űܰ�����(2dTexture)
	//�ؽ��ĵ� �ٸ� �׷��Ƚ� ��ü�� ���� view�� ���ؼ� ���� shader���� �����ϴ� view(shaderview)�� ���� ���� �ؽ��İ� shader�� ���ؼ� ��µǱ� ������ 
	//shader���� ������ۿ� ���� slot�� ������ ���۴�b �ؽ��Ĵ� t�� ����
}


