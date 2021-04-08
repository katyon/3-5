
struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

Texture2D texture_rgb	: register(t0);
Texture2D texture_alphe : register(t1);
SamplerState texture_map_sampler_state : register( s0 );

float4 main(VS_OUT pin) : SV_TARGET
{
	float3 rgb = texture_rgb.Sample(texture_map_sampler_state, pin.texcoord).rgb;
	float alphe = texture_alphe.Sample(texture_map_sampler_state, pin.texcoord).a;
	return float4(rgb,alphe);
}