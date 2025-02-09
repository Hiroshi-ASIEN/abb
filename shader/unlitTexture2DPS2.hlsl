
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse *= In.Diffuse;
    }
    else
    {
        outDiffuse = In.Diffuse;
    }

	
	// �A���t�@�f�B�U
	// �e�N�X�`�����W�̎΂ߕ�����200�{�ɂ���
	// 0�`1�����̊Ԃ�t�ɓ���
	// ///������Ȋ����ŕ`�悷�邵�Ȃ��𕪂��ē����Ɍ�����
	// �Ԍ˓I��
    float t = frac((In.TexCoord.x + In.TexCoord.y) * 200);
    clip(outDiffuse.a - t);

}
