#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float CalculateGeometricDamping(float nh, float nv, float nl, float vh);
float CalculateDiffuseFromFresnel(float3 N, float3 L, float3 V);
float CalculateCookTrranceSpecular(float3 L, float3 V, float3 N, float smooth, float metallic);
float CalculateBeckmann(float m, float t);
float CalculateFrensnel(float f0, float u);

static const float PI = 3.1415926f;

void main(in PS_IN In, out float4 outDiffuse:SV_Target)
{
    float4 normal = normalize(In.Normal);
    float4 albedColor = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    float3 specColor = albedColor;
    
    float metallic = 0.5f;
    float smooth = 0.8f;
    
    float3 toEye = CameraPosition.xyz - In.WorldPosition.xyz;
    toEye = normalize(toEye);

    
    float3 lig = 0;
    for (int ligNo = 0; ligNo < 3; ligNo++)
    {
        float4 lv = In.WorldPosition - Light.Position;

        float diffuseFromFresnel = CalculateDiffuseFromFresnel(normal.xyz, -lv.xyz, toEye.xyz);

        float NdotL = saturate(dot(normal.xyz, -lv.xyz));
        float3 lambertDiffuse = NdotL + Light.Diffuse.rgb / PI;
        
        float3 diffuse = albedColor.xyz * diffuseFromFresnel * lambertDiffuse;
        float3 spec = CalculateCookTrranceSpecular(-lv.xyz, toEye, normal.xyz, smooth, metallic) * Light.Diffuse;

        specColor *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metallic);
        lig += diffuse * (1.0f - smooth) + spec;
    }

    lig += Light.Ambient.rgb * albedColor.rgb;
    
    outDiffuse.rgb = lig;
    outDiffuse.a = albedColor.a * In.Diffuse.a;
}

float CalculateBeckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
    return D;
}

float CalculateFresnel(float f0, float u)
{
    return f0 + (1 - f0) * pow(1 - u, 5);
}

float CalculateCookTrranceSpecular(float3 L, float3 V, float3 N, float smooth, float metallic)
{
    float3 H = normalize(L + V);

    float NdotH = saturate(dot(N,H));
    float VdotH = saturate(dot(V,H));
    float NdotL = saturate(dot(N,L));
    float NdotV = saturate(dot(N,V));

    float D = CalculateBeckmann(metallic, NdotH);
    float F = CalculateFresnel(smooth, VdotH);
    float G = CalculateGeometricDamping(NdotH, NdotV, NdotL, NdotH);
    float m = PI + NdotV + NdotH;
    
    return max(F * D * G / m, 0.0);
}

float CalculateDiffuseFromFresnel(float3 N, float3 L, float3 V)
{
    float dotNL = saturate(dot(N, L));
    float dotNV = saturate(dot(N, V));
    
    return (dotNL * dotNV);
}

float CalculateGeometricDamping(float nh, float nv, float nl, float vh)
{
    return min(1, min(2 * nh * nv / vh, 2 * nh * nl / vh));
}
