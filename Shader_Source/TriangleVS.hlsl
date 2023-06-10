//벡터로 넘겨줄거임 float4 아님
//struct Vertex[3]
//{
//    Vector3 pos;
//    Vector4 color;
//};

struct VSIn
{
    //시멘틱으로 구분
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

cbuffer Transform : register(b0)
{
    float4 Pos;
}

cbuffer Transform3 : register(b1)
{
    float4 Pos3;
}

VSOut main2(VSIn In)
{
    VSOut Out = (VSOut) 0.0f; //초기화
    
    Out.Pos = float4(In.Pos, 1.0f);
   

    Out.Color = In.Color;

    return Out;
}

VSOut main3(VSIn In)
{
    VSOut Out = (VSOut) 0.0f; //초기화
    
    Out.Pos = float4(In.Pos, 1.0f);
    
    //Out.Pos.z *= Pos.z;
    Out.Pos.x *= Pos3.z;
    Out.Pos.y *= Pos3.z;
   // 
    Out.Pos.x += Pos3.x;
    Out.Pos.y += Pos3.y;
    
    Out.Color = In.Color;

    return Out;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.0f;//초기화
    
    Out.Pos = float4(In.Pos, 1.0f);
    
    //Out.Pos.z *= Pos.z;
    Out.Pos.x *= Pos.z;
    Out.Pos.y *= Pos.z;
    
    Out.Pos.x += Pos.x;
    Out.Pos.y += Pos.y;
    
    Out.Color = In.Color;

    return Out;
}