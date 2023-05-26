#pragma once
#include "Engine.h"
#include "WGraphicDevice_Dx11.h"


using namespace W::math;
namespace W::renderer
{
	struct Vertex
	{
		Vector3 Pos;
		Vector4 Color;
	};

	extern Vertex vertexes[];
	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	//(юс╫ц)
	extern Vertex Circlevertexes[];
	extern ID3D11InputLayout* lineLayout;
	extern ID3D11Buffer* lineBuffer;
	extern ID3DBlob* lineVSBlob;
	extern ID3D11VertexShader* lineVSShader;
	extern ID3DBlob* linePSBlob;
	extern ID3D11PixelShader* linePSShader;


	void Initialize();
	void InitializeCircle();
}

