
Texture2D DiffuseTexture : register(t0);
SamplerState DecalSampler : register(s0);
cbuffer CBPerFrame1 : register(b1)
{
	float	ContrastWeight;	//コントラスト調整
	float	Bright;			//明度調整
	float	threshold;		//閾値
	int		flg;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};
float4 main(VS_OUT input) : SV_TARGET
{
	float4 color = (float4)0;
	float2 Tex = input.texcoord;

	color = DiffuseTexture.Sample(DecalSampler, Tex);
	if (flg == 0)return color;
	// 閾値からの差
	float3 offsets = color.rgb - threshold;
	// コントラスト　
	color.rgb = threshold + offsets * ContrastWeight;

	// 明度調整
	color.rgb += Bright;

	return color;
}