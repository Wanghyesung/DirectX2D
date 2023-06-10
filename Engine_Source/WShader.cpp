#include "WShader.h"


namespace W
{
	Shader::Shader():
		m_tInputLayout(nullptr),
		m_eTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{

	}

	Shader::~Shader()
	{
		m_tInputLayout->Release();
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool Shader::Create(const eShaderStage _eStage, 
		const std::wstring& _wstrFileName, 
		const std::string& _strFuncName)
	{
		std::filesystem::path shaderPath =
			std::filesystem::current_path().parent_path();

		shaderPath += L"\\Shader_Source\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += _wstrFileName;

		ID3DBlob* errorBlob = nullptr;
		if (_eStage == eShaderStage::VS)
		{
			GetDevice()->CompileFromfile(fullPath, _strFuncName, "vs_5_0", m_cpVSBlop.GetAddressOf());
			GetDevice()->CreateVertexShader(m_cpVSBlop->GetBufferPointer(),
				m_cpVSBlop->GetBufferSize(), m_cpVS.GetAddressOf());
		}
		else if (_eStage == eShaderStage::PS)
		{
			GetDevice()->CompileFromfile(fullPath, _strFuncName, "ps_5_0", m_cpPSBlop.GetAddressOf());
			GetDevice()->CreatePixelShader(m_cpPSBlop->GetBufferPointer(),
				m_cpPSBlop->GetBufferSize(), m_cpPS.GetAddressOf());
		}


		return true;
	}

	void Shader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(m_eTopology);
		GetDevice()->BindInputLayout(m_tInputLayout);


		GetDevice()->BindVertexShader(m_cpVS.Get());
		GetDevice()->BindPixelShader(m_cpPS.Get());
	}
}

