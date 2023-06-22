#include "WMaterial.h"


namespace W::graphics
{
	Material::Material() :
		Resource(W::enums::eResourceType::Material),
		m_pShader(nullptr),
		m_pTex(nullptr)
	{
	}
	Material::~Material()
	{
		
	}
	HRESULT Material::Load(const std::wstring& _strPath)
	{
		return E_NOTIMPL;
	}
	void Material::Binds()
	{
		m_pTex->BindShader(eShaderStage::PS, 0);
		m_pShader->Binds();
	}
	void Material::Clear()
	{
		m_pTex->Clear();
	}
}