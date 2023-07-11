#include "WShader.h"
#include "WRenderer.h"

namespace W
{
	Shader::Shader():
		Resource(enums::eResourceType::Shader),
		m_tInputLayout(nullptr),
		m_eTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
		m_eRSType(eRSType::SolidBack),
		m_eDSType(eDSType::Less),
		m_eBSType(eBSType::AlphaBlend)
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

		//레이터라이저 단계
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> cpRSstate = renderer::m_cpRasterizerStates[(UINT)m_eRSType];
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> cpDSstate = renderer::m_cpDepthStencilStates[(UINT)m_eDSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> cpBSstate = renderer::m_cpBlendStates[(UINT)m_eBSType];

		GetDevice()->BindRasterizeState(cpRSstate.Get());
		//GetDevice()->BindDepthStencilState(cpDSstate.Get());
		GetDevice()->BindBlendState(cpBSstate.Get());
	}
}

