
// High-level Shader Language (고급 셰이더 언어)
// Dx API에 사용되는 셰이딩 언어
// 그 중에 버텍스 셰이더 형식을 사용 중이다.



// 
// hlsl 파일을 사용하려면 속성에서 진입점에 하단 함수명같은 코드를 사용해야 한다.
float4 VertexShaderFunction(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}