
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

	
	// アルファディザ
	// テクスチャ座標の斜め方向を200倍にする
	// 0～1未満の間がtに入る
	// ///←こんな感じで描画するしないを分けて透明に見せる
	// 網戸的な
    float t = frac((In.TexCoord.x + In.TexCoord.y) * 200);
    clip(outDiffuse.a - t);

}
