//���ͷ� �Ѱ��ٰ��� float4 �ƴ�
//struct Vertex[3]
//{
//    Vector3 pos;
//    Vector4 color;
//};

struct VSIn
{
    //�ø�ƽ���� ����
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

cbuffer Transform : register(b0)
{
    //float4 Position;
    //�� �켱 ���
    row_major matrix World;
    row_major matrix View;
    row_major matrix Projection;
}


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f; //�ʱ�ȭ
    
    //�������
    float4 world = mul(float4(In.Pos, 1.f), World);
    //������� * �����
    //float4 view = mul(world, View);
    //����� * �������
    //float4 proj = mul(view, Projection);
    
    Out.Pos = world;
    Out.UV = In.UV;
    Out.Color = In.Color;

    return Out;
}