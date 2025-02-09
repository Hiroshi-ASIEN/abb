
#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // �����x�N�g��
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);

    // �@���x�N�g��
    float3 normal = normalize(In.Normal.xyz);
/*            float3 vx, vz, vn;
            vx.x = In.Position.x;
            vx.y = In.Position.y;
            vx.z = In.Position.z;
    vz.x = In.Position.x;
    vz.y = In.Position.y;
    vz.z = In.Position.z;

				// �O��
            vn.x = vz.y * vx.z - vz.z * vx.y;
            vn.y = vz.z * vx.x - vz.x * vx.z;
            vn.z = vz.x * vx.y - vz.y * vx.x;

				// ���K��
        vn = normalize(vn);
    
            normal = vn;
*/
    // ���˃x�N�g��
    float3 refv = reflect(eyev.xyz, normal);
    refv = normalize(refv);
    
    // ���}�b�s���O�e�N�X�`�����W
    float2 envTexCoord;
//    envTexCoord.x = refv.x * 0.5 + 0.5;
//   envTexCoord.y = -refv.y * 0.5 + 0.5;    // �c�������t�ɂȂ��Ă��܂��ׁAy�̂݃}�C�i�X
    envTexCoord.x = refv.x * 0.3 + 0.5;
    envTexCoord.y = -refv.y * 0.3 + 0.5;
    
    
    float3 texRGB = g_Texture.Sample(g_SamplerState, In.TexCoord).rgb;
    texRGB *= 0.9f;
    float3 envRGB = g_TextureEnv.Sample(g_SamplerState, envTexCoord).rgb;
    envRGB *= 0.1f;
    
    
    // ���}�b�s���O
    outDiffuse.rgb = texRGB + envRGB;
    outDiffuse.a = 1.0f;
    outDiffuse.a = Material.Diffuse.a;
}
