
cbuffer TransformData : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};


// SV : System Value, "�ǹ� ü��"
// 
// SV_POSITION : Vertex Output -> Pixel Shader �� �̵� �� ����ϴ� �ø�ƽ
// SV_Target : �ȼ� ���̴��� ���� ���� Ÿ�� ��ġ�� Sementic Name