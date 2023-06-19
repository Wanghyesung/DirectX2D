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
		//scratchImage원본이미지의 정보들이 들어있는 확장자
		ScratchImage m_Image;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpTexture;//2d이미지
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cpSRV;//shader접근할 view
		D3D11_TEXTURE2D_DESC m_tDesc;
	};

	//텍스쳐(uv좌표)의 픽셀을 하나하나 옮겨가져옴(2dTexture)
	//텍스쳐도 다른 그래픽스 객체와 같이 view를 통해서 접근 shader에서 접근하는 view(shaderview)가 따로 있음 텍스쳐가 shader을 통해서 출력되기 떄문에 
	//shader또한 상수버퍼와 같이 slot을 구분함 버퍼는b 텍스쳐는 t로 구분
}


