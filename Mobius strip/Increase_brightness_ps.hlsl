
Texture2D DiffuseTexture : register(t0);
SamplerState DecalSampler : register(s0);
cbuffer CBPerFrame1 : register(b1)
{
	float	ContrastWeight;	//�R���g���X�g����
	float	Bright;			//���x����
	float	threshold;		//臒l
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
	// 臒l����̍�
	float3 offsets = color.rgb - threshold;
	// �R���g���X�g�@
	color.rgb = threshold + offsets * ContrastWeight;

	// ���x����
	color.rgb += Bright;

	return color;
}