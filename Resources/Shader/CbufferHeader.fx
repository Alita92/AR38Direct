
cbuffer TransformData : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};


// SV : System Value, "의미 체계"
// 
// SV_POSITION : Vertex Output -> Pixel Shader 의 이동 간 사용하는 시멘틱
// SV_Target : 픽셀 셰이더를 보낼 렌더 타겟 위치의 Sementic Name