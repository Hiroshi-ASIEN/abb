#include "common2.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float CalculateBeckmann(float m, float cosbeta);
float CalculateFresnel(float n, float c);
float CalculateGeometricDamping(float nh, float nv, float nl, float vh);
void main (in PS_IN In,out float4 outDiffuse:SV_Target)
{
    float4 lv = Light.Position - In.WorldPosition;
    float4 ld = length(lv);
    lv = normalize(lv);
    
    float ofs = 1.0f - (1.0f / Light.PointParam.x) * ld;
    ofs = max(0, ofs);
    
    float4 normal = normalize(In.Normal);
    float light = 0.5f + 0.5f * dot(normal.xyz, lv.xyz);
    light *= ofs;

    //===================================
    // �e�N�X�`�����J���[�ݒ肩�I��
    //�e�N�X�`���̃s�N�Z���F���擾
//        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
//        float4 metalcolor = outDiffuse;
    
    // �J���[�ݒ�i�f�ނ̐F�͈�U�K���j
//    float4 metalcolor = float4(0.7f, 0.6f, 0.3f, 1.0f); 
 //   float4 metalcolor = float4(0.3f, 0.4f, 0.6f, 1.0f); // �f�ނ̐F�͈�U�K��
    float4 metalcolor = float4(1.0f, 1.0f, 1.0f, 1.0f); // �f�ނ̐F�͈�U�K��

    outDiffuse = metalcolor;
    //===================================
    
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    outDiffuse.a = In.Diffuse.a;
    outDiffuse.rgb += Light.Ambient.rgb;
    
    float3 eyev = CameraPosition.xyz - In.WorldPosition.xyz;
    eyev = normalize(eyev);
    
    float3 halfv = eyev + lv.xyz;
    halfv = normalize(halfv);

    // �X�y�L�����v�ZCook-Trrance���f��
    float3 specular;
    float nv = dot(normal.xyz, eyev);
    float nh = dot(normal.xyz, halfv);
    float vh = dot(eyev, halfv);
    float nl = dot(normal.xyz, lv.xyz);
    
    float D = CalculateBeckmann(0.3, nh);                   // �ʂ̑e��
    float G = CalculateGeometricDamping(nh, nv, nl, vh);    // �􉽌�����
    float F = CalculateFresnel(0.8f, dot(lv.xyz, halfv));   // ������
    
    // �X�y�L�������F���Ƃ��Čv�Z�����
    specular = max(0.0f, F * D * G / nv) * metalcolor.rgb;
    outDiffuse.rgb += (specular * ofs);
    
}

// �}�C�N���t�@�Z�b�g���z�֐�
// smooth:�ʂ̑e�������߂�p�����[�^�[
float CalculateBeckmann(float smooth, float nh)
{
    float D;
    D = (
            exp(-(1 - (nh * nh)) / (smooth * smooth * nh * nh))
            / (4 * smooth * smooth * nh * nh * nh * nh)
        );
    
    return D;

}

// �t���l����
float CalculateFresnel(float metal,float hv)
{
    // Schlick�ߎ�metal�l��0.0 - 1.0�Ƃ���
    return metal + (1.0f - metal) * pow(1.0f - hv, 5);

/*    
    // ���ʂɌv�Zmetal�l��0.0�ȏ�Ƃ���
    float F;
    float g = sqrt(metal * metal + hv * hv - 1);
    float T1 = ((g - hv) * (g - hv)) / ((g + hv) * (g + hv));
    float T2 = 1 + ((hv * (g + hv) - 1) * (hv * (g + hv) - 1))
                / ((hv * (g - hv) + 1) * (hv * (g - hv) + 1));
    F = 0.5 * T1 * T2;
    
    return F;
*/
}

// �􉽌�����
float CalculateGeometricDamping(float nh, float nv, float nl, float vh)
{
    float G;
    G = min(1, min(2 * nh * nv / vh, 2 * nh * nl / vh));
    
    return G;

}