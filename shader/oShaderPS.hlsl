
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


//�����_���m�C�Y
//�K���Ȓl�����ɋ^���������v�Z����
float Rand(float2 coord)
{
	//frac(x)��x�̏�������Ԃ��@������ 0.0 <=�@r < 1.0f�̒l�ɂȂ�	
    return frac(sin(dot(coord.xy, float2(12.9898f, 78.233f))) * 43758.5453f);
}
/*
static float x,y;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float2 uv = In.TexCoord;
    
    float2 len = float2(0.5f, 0.5f); // ���S���W(Texture���W)�����Ēu��
    len -= In.TexCoord.xy; // �s�N�Z������~�̒��S�ւ̃x�N�g��
    x = x + 0.1f;
    y = y - 0.001f;
    len.y /= (x /y);

    len = length(len); // �x�N�g���̒���
//    if (len.x < 0.1f)  // ������0.3�����̏ꍇ�̓��U�C�N����
    {
        // ���U�C�N����
        uv *= float2(x, y); // ��ʍ��W�֕ϊ�
        uv /= x; // �z����W�֕ϊ�
        uv = floor(uv) * x; // ��`�̍�����W
        uv /= float2(x, y); // �e�N�X�`�����W�֖߂�
 
    }
    outDiffuse = g_Texture.Sample(g_SamplerState, uv); // �e�N�X�`���̐F���o��
    outDiffuse *= In.Diffuse; // �|���S���̃s�N�Z���F������
    
    
    
}
*/


//==================================================
// �G���g���[�֐�
//==================================================
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // ���̃s�N�Z���Ɏg���e�N�Z�����擾
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    
    // �����쐬
    float noise = Rand(In.TexCoord * Parameter.z);
    // �����͈̔͂𒲐�
    noise = clamp(noise, 0.2f, 0.5f);
    // �e�N�X�`���̐F�։��Z
    outDiffuse.rgb += noise;
    
    // �O���[�X�P�[����
    {
    // �ŏI�I��outDiffuse.rgb��Y�̒l�ɂ���
    // outDiffuse.a�̒l�͕ύX���Ȃ��悤�ɒ���
    
    //    float Y = 0;
    //    Y = ((0.299 * outDiffuse.r) +
    //     (0.587 * outDiffuse.g) +
    //    (0.114 * outDiffuse.b));
    //    outDiffuse.rgb = Y;
    
    // �p�^�[��1
    //    outDiffuse.rgb = ((0.299 * outDiffuse.r) +
    //                       (0.587 * outDiffuse.g) +
    //                        (0.114 * outDiffuse.b));

        // �p�^�[�� 2
    //   outDiffuse.r = Y;
    //    outDiffuse.g = Y;
    //    outDiffuse.b = Y;

    // �p�^�[��3 ���ϊ֐��𗘗p����ꍇ
//        float3 sirokuro = float3(0.299f, 0.587f, 0.114f);
 //       outDiffuse.rgb = dot(outDiffuse.rgb, sirokuro);
    
    // Y=0.299*R + 0.587*G + 0.114*B
    }

    // ��悵�Ă݂�Ǝ������ς�����肷��
    outDiffuse.rgb *= outDiffuse.rgb;
    outDiffuse.a = Material.Diffuse.a;
    
    // �e�N�Z���̏��Ƀs�N�Z���̃f�t���[�Y�F����Z����
    outDiffuse.rgb *= In.Diffuse.rgb;

}
