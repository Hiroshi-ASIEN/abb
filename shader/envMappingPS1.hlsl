
#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

static const float PI = 3.141592653589;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // �����x�N�g��
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);

    // �@���x�N�g��
    float3 normal = normalize(In.Normal.xyz);

    // ����
    float3 refColor;
    {
    // ���˃x�N�g��
    float3 refv = reflect(eyev.xyz, normal);
    refv = normalize(refv);
    
    // ���}�b�s���O�e�N�X�`�����W (�X�t�B�A�}�b�v�p)
//    float2 envTexCoord;
//    envTexCoord.x = refv.x * 0.5 + 0.5;
//   envTexCoord.y = -refv.y * 0.5 + 0.5;    // �c�������t�ɂȂ��Ă��܂��ׁAy�̂݃}�C�i�X
//    envTexCoord.x = refv.x * 0.3 + 0.5;
//   envTexCoord.y = -refv.y * 0.3 + 0.5;

    // ���}�b�s���O�e�N�X�`�����W(�p�m���})
    float2 envTexCoord;
    envTexCoord.x = atan2(refv.x, refv.z) / (PI * 2);
    envTexCoord.y = atan(refv.y) / PI;
    
    // ���}�b�s���O
    /*
    outDiffuse.rgb = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    outDiffuse.a = 1.0f;
    outDiffuse.a = Material.Diffuse.a;
    */    
    refColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord).rgb;
    }

    // ����
    float3 refrColor;
    {
    // ���܃x�N�g��   
    float3 refrv = refract(eyev.xyz, normal, 1.0f / 1.5f);
    refrv = normalize(refrv);
    
    // ���}�b�s���O�e�N�X�`�����W(�p�m���})
    float2 envTexCoord;
    envTexCoord.x = atan2(refrv.x, refrv.z) / (PI * 2);
    envTexCoord.y = atan(refrv.y) / PI;
    
    // ���܃}�b�s���O
        /*
    outDiffuse.rgb += g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    outDiffuse *= 0.7f;
    outDiffuse.a = 1.0f;
    outDiffuse.a = Material.Diffuse.a;
        */
    refrColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord).rgb;
    }

    // �t���l�����˗�  (Schlick�ߎ���)
    float f0 = 0.04f;   
    float d = saturate(dot(-eyev, normal));
//    float fresnel = f0 + (1.0f - f0) * pow((1.0f - d), 5.0f);
    float fresnel = f0 + (1.0f - f0) * pow((1.0f - d), 2.0f);

    outDiffuse.rgb = lerp(refrColor, refColor, fresnel);
    outDiffuse.a = Material.Diffuse.a;
}
