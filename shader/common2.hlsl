
//common2.hlsl


//C���ꂩ��󂯎������i�[����ϐ�
//�R���X�^���g�o�b�t�@�̓��e�������ɓ���

cbuffer		WorldBuffer : register(b0)//�萔�o�b�t�@0��
{
	matrix	World;	//���[���h�s��
}

cbuffer ViewBuffer : register(b1)//�萔�o�b�t�@1��
{
	matrix	View;	//�J�����s��
}

cbuffer ProjectionBuffer : register(b2)//�萔�o�b�t�@2��
{
	matrix	Projection;	//�v���W�F�N�V�����s��
}

//���_�̃f�[�^�\����
struct VS_IN
{
	float4		Position	: POSITION0;//�|�W�V�����[��
	float4		Normal		: NORMAL0;	//�m�[�}���[��
	float4		Diffuse		: COLOR0;	//�J���[�[��
	float2		TexCoord	: TEXCOORD0;	//�e�N�X�R�[�h�[��
};//�\������|���S���̒��_���C�A�E�g�Ɠ���

//�s�N�Z���V�F�[�_�[�֓��͂����s�N�Z�����
struct PS_IN
{
	float4		Position		: SV_POSITION;	//�s�N�Z���̉�ʍ��W
	float4		WorldPosition	: POSITION0;	//�s�N�Z���̋�Ԃł̍��W
	float4		Normal			: NORMAL0;		//�s�N�Z���̖@��
	float4		Diffuse			: COLOR0;		//�s�N�Z���̐F
	float2		TexCoord		: TEXCOORD0;	//�s�N�Z���̃e�N�X�`�����W
};

//���C�g�\���̂̒�`�@C���ꑤ��LIGHT�\���̂Ɠ������e
struct LIGHT
{
	bool	Enable;//bool�^����float�^�ł��܂�����Ă���Ă���
	bool3	Dummy;
	float4	Direction;
	float4	Diffuse;
	float4	Ambient;
	
    float4 SkyColor;		// �V���F
    float4 GroundColor;		// �n�ʐF
    float4 GroundNormal;	// �n�ʖ@��
	
    float4 Position;		// ���W
    float4 PointParam;		// ���͈̔�
};
cbuffer		LightBuffer : register(b4)//�R���X�^���g�o�b�t�@�S�ԂŎ󂯎��
{
	LIGHT	Light;	//���C�g�^�\���̂Ƃ��ė��p����
}

cbuffer CameraBuffer : register(b5)	//�o�b�t�@5��
{
	float4	CameraPosition;	//�J�����̍��W
}


//==================================================
// �ėp�p�����[�^�[�󂯎��p
//==================================================
cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter;	//  C���ꑤ���牽���󂯎��
	
	
}

//////////////////EOF////////////////////////////////////////////






