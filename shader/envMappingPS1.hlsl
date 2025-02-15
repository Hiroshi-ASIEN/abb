
#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

static const float PI = 3.141592653589;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // 視線ベクトル
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);

    // 法線ベクトル
    float3 normal = normalize(In.Normal.xyz);

    // 反射
    float3 refColor;
    {
    // 反射ベクトル
    float3 refv = reflect(eyev.xyz, normal);
    refv = normalize(refv);
    
    // 環境マッピングテクスチャ座標 (スフィアマップ用)
//    float2 envTexCoord;
//    envTexCoord.x = refv.x * 0.5 + 0.5;
//   envTexCoord.y = -refv.y * 0.5 + 0.5;    // 縦方向が逆になってしまう為、yのみマイナス
//    envTexCoord.x = refv.x * 0.3 + 0.5;
//   envTexCoord.y = -refv.y * 0.3 + 0.5;

    // 環境マッピングテクスチャ座標(パノラマ)
    float2 envTexCoord;
    envTexCoord.x = atan2(refv.x, refv.z) / (PI * 2);
    envTexCoord.y = atan(refv.y) / PI;
    
    // 環境マッピング
    /*
    outDiffuse.rgb = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    outDiffuse.a = 1.0f;
    outDiffuse.a = Material.Diffuse.a;
    */    
    refColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord).rgb;
    }

    // 屈折
    float3 refrColor;
    {
    // 屈折ベクトル   
    float3 refrv = refract(eyev.xyz, normal, 1.0f / 1.5f);
    refrv = normalize(refrv);
    
    // 環境マッピングテクスチャ座標(パノラマ)
    float2 envTexCoord;
    envTexCoord.x = atan2(refrv.x, refrv.z) / (PI * 2);
    envTexCoord.y = atan(refrv.y) / PI;
    
    // 屈折マッピング
        /*
    outDiffuse.rgb += g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    outDiffuse *= 0.7f;
    outDiffuse.a = 1.0f;
    outDiffuse.a = Material.Diffuse.a;
        */
    refrColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord).rgb;
    }

    // フレネル反射率  (Schlick近似式)
    float f0 = 0.04f;   
    float d = saturate(dot(-eyev, normal));
//    float fresnel = f0 + (1.0f - f0) * pow((1.0f - d), 5.0f);
    float fresnel = f0 + (1.0f - f0) * pow((1.0f - d), 2.0f);

    outDiffuse.rgb = lerp(refrColor, refColor, fresnel);
    outDiffuse.a = Material.Diffuse.a;
}
