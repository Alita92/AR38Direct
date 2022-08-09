#include "CbufferHeader.fx"

struct VertexIn
{
    // ���ؽ� ���̴��� �Է����� ���� �ø�ƽ �� ��, ����ü�� ������.
    float4 Position : POSITION;
    float4 Texcoord : TEXTURECOORD;
};

struct VertexOut
{
    // ���ؽ� ���̴��� ������� ������ �ø�ƽ �� ��.
    float4 Position : SV_POSITION;
    float4 Texcoord : TEXTURECOORD;
};


cbuffer TextureCutData : register(b1)
{
    // 0.0f 0.0f 
    float2 TextureCutDataPos;
    // 1 / 8 1 / 8
    float2 TextureCutDataSize;
};


// '�ؽ�ó' �� ���� ���ؽ� ���̴�
VertexOut Texture_VS(VertexIn _in)
{
    VertexOut Out;

    Out.Position = _in.Position;

  
    Out.Position.w = 1.0f;
    Out.Position = mul(Out.Position, WVP);
    // �޾Ƶ��� POSITION �� ����X��X���� ����� ������ �۾�
    
    // 0 0 
    // 1, 0
    // 1, 1
    //                   1                 0.125             +      0.125 * _x
    Out.Texcoord.x = (_in.Texcoord.x * TextureCutDataSize.x) + TextureCutDataPos.x;
    //                   1                 0.125             +      0.125 * _x
    Out.Texcoord.y = (_in.Texcoord.y * TextureCutDataSize.y) + TextureCutDataPos.y;

    return Out;
}

cbuffer ResultColor : register(b0)
{
    float4 vColor;
};


Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
// ���ҽ� ���� register() ��, GPU�� �������� �� �ִ� ����̴�.
// �ִ� 15���� ������� �� ������, �� ���۴� �� 4096���� ��� ������ ������ �� �ִ�.
// b : ��� ����
// t : �ؽ�ó
// s : ���÷�
// �ڿ� �ٴ� ���ڴ� ����

// '�ؽ�ó' �� ���� �ȼ� ���̴�
float4 Texture_PS(VertexOut _in) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _in.Texcoord.xy) * vColor;

    if (0.0f == Color.a)
    {
        clip(-1);
    }
        

    return Color;
}


