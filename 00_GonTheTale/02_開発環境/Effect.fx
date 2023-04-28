// -------------------------------------------------------------
// ���ʔ��ˌ�
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------

float4x4 mWVP;

float4 vLightDir;	// ���C�g�̕���
float4 vColor;		// ���C�g�����b�V���̐F
float3 vEyePos;		// �J�����̈ʒu�i���[�J�����W�n�j
// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float4 Color		: COLOR0;
	float2 Tex			: TEXCOORD0;
	float3 N			: TEXCOORD2;		//�@��
	float3 X			: TEXCOORD1;
};

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture Tex;
sampler Samp = sampler_state
{
	Texture = <Tex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = WRAP;
	AddressV = WRAP;
};

//=========================================
// ���_�V�F�[�_�[
//=========================================
VS_OUTPUT VS(
	float4 Pos    : POSITION,	// ���[�J���ʒu���W
	float4 Normal : NORMAL,		// �@���x�N�g��
	float2 Tex : TEXCOORD		// �e�N�X�`���̖@���x�N�g��
) {
	VS_OUTPUT Out = (VS_OUTPUT)0;		// �o�̓f�[�^

	// ���W�ϊ�
	Out.Pos = mul(Pos, mWVP);

	// �e�N�X�`�����W
	Out.Tex = Tex;

	// �g�U���{����
	float amb = -vLightDir.w;	// �����̋���
	float3 L = -vLightDir;		// ���[�J�����W�n�ł̃��C�g�x�N�g��
	Out.Color = vColor * max(amb, dot(Normal, -vLightDir));

	// ���ʔ��˗p�̃x�N�g��
	Out.N = Normal.xyz;
	Out.X = Pos.xyz;

	return Out;
}

//=========================================
//�s�N�Z���V�F�[�_�[
//=========================================
float4 PS(VS_OUTPUT In) : COLOR
{
	float3 L = vLightDir.xyz;				// ���C�g�x�N�g��
	float3 N = normalize(In.N);				// �@���x�N�g��
	float3 V = normalize(vEyePos - In.X);	// �����x�N�g��
	float3 H = normalize(L + V);			// �n�[�t�x�N�g��

	// �v�Z�Ɏg�����ꂼ��̊p�x
	float NV = dot(N,V);
	float NH = dot(N,H);
	float VH = dot(V,H);
	float NL = dot(N,L);
	float LH = dot(L,H);

	// Beckmann ���z�֐�
	const float m = 0.35f;// �r���A���̍L����
	float NH2 = NH*NH;
	float D = exp(-(1 - NH2) / (NH2*m*m)) / (4 * m*m*NH2*NH2);

	// �􉽌�����
	float G = min(1,min(1 * NH*NV / VH, 2 * NH*NL / VH));

	// �t���l��
	float n = 20.0f;	// ���f���ܗ��̎���
	float g = sqrt(n*n + LH*LH - 1);
	float gpc = g + LH;
	float gnc = g - LH;
	float cgpc = LH*gpc - 1;
	float cgnc = LH*gnc + 1;
	float F = 0.5f * gnc * gnc * (1 + cgpc * cgpc / (cgnc * cgnc)) / (gpc * gpc);

	float4 Ambient = { 0.0f,0.0f,0.0f, 1.0f };

	return In.Color + Ambient;		// �g�U���{����(�e�N�X�`���̐F)
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique Diffuse
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
