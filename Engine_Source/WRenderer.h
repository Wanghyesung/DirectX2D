#pragma once
#include "Engine.h"
#include "WGraphicDevice_Dx11.h"
#include "WMesh.h"
#include "WShader.h"
#include "WConstantBuffer.h"
#include "WCamera.h"

using namespace W::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 Pos;
		Vector4 Color;
		Vector2 UV;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix m_mWorld;
		Matrix m_mView;
		Matrix m_mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		//카메라 위치 카메라 사이즈, 해상도 크기
		Vector4 m_vCameraPosition;
		Vector2 m_vCameraScale;
		Vector2 m_vResolution;
	};

	extern Vertex vertexes[];
	//extern ID3D11InputLayout* triangleLayout;
	//extern ID3D11Buffer* triangleBuffer;
	//extern ID3D11Buffer* triangleIdxBuffer;
	//extern W::Mesh* mesh;
	//extern ID3DBlob* errorBlob;
	//extern ID3DBlob* triangleVSBlob;
	//extern ID3D11VertexShader* triangleVSShader;
	//extern ID3DBlob* trianglePSBlob;
	//extern W::Shader* shader;
	//extern ID3D11PixelShader* trianglePSShader;

	extern W::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState[(UINT)eSamplerType::End];
	
	//레스터라이저, 뎁스텐실, 블렌드
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_cpRasterizerStates[(UINT)eRSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_cpDepthStencilStates[(UINT)eDSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> m_cpBlendStates[(UINT)eBSType::End];

	extern std::vector<W::Camera*> vecCameras;

	void Render();
	void Initialize();
	void Release();
}

