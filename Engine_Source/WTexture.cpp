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
		//�ȼ� ���̴��� texture(shaderResource)�� �����ֱ� �ؽ����� �ȼ��� ����ϱ�
		//�ؽ��� ��ǥ uv��ǥ ����, �̹����� �� ȭ���� ũ�Ⱑ �ٸ��� ������ �Ǿ �;��� (���ø�) samplerstate(���ø��ɼ�)
		
		GetDevice()->BindShaderResource(_eStage, _iStartSlot, m_cpSRV.GetAddressOf());
	}
	void Texture::Clear()
	{
		//���� nullptr�� ��� �����
		ID3D11ShaderResourceView* srv = nullptr;

		GetDevice()->BindShaderResource(eShaderStage::VS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, 0, &srv);
	}
}

