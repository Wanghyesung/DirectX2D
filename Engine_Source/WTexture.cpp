#include "WTexture.h"
#include "WGraphicDevice_Dx11.h"

namespace W::graphics
{
	Texture::Texture():
		Resource(enums::eResourceType::Texture),
		m_Image{},
		m_cpTexture(nullptr),
		m_cpSRV(nullptr),
		m_tDesc{}
	{
	}
	Texture::~Texture()
	{
		
	}
	HRESULT Texture::Load(const std::wstring& _strPath)
	{
		wchar_t szExtension[50] = {};
		_wsplitpath_s(_strPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);
		
		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(_strPath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(_strPath.c_str(), nullptr, m_Image)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(_strPath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image)))
				return S_FALSE;
		}

		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, m_Image.GetImages()
			, m_Image.GetImageCount()
			, m_Image.GetMetadata()
			, m_cpSRV.GetAddressOf()
		);
		m_cpSRV->GetResource((ID3D11Resource**)m_cpTexture.GetAddressOf());
		
		return S_OK;
	}
	void Texture::BindShader(eShaderStage _eStage, UINT _iStartSlot)
	{
		//픽셀 셰이더와 texture(shaderResource)로 묶어주기 텍스쳐의 픽셀을 출력하기
		//텍스쳐 좌표 uv좌표 셋팅, 이미지와 내 화편의 크기가 다르면 보간이 되어서 와야함 (샘플링) samplerstate(샘플링옵션)
		
		GetDevice()->BindShaderResource(_eStage, _iStartSlot, m_cpSRV.GetAddressOf());
	}
	void Texture::Clear()
	{
		//전부 nullptr로 묶어서 지우기
		ID3D11ShaderResourceView* srv = nullptr;

		GetDevice()->BindShaderResource(eShaderStage::VS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, 0, &srv);
	}
}

