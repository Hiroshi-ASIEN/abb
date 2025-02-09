
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


//ランダムノイズ
//適当な値を元に疑似乱数を計算する
float Rand(float2 coord)
{
	//frac(x)はxの小数部を返す　乱数は 0.0 <=　r < 1.0fの値になる	
    return frac(sin(dot(coord.xy, float2(12.9898f, 78.233f))) * 43758.5453f);
}
/*
static float x,y;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float2 uv = In.TexCoord;
    
    float2 len = float2(0.5f, 0.5f); // 中心座標(Texture座標)を入れて置く
    len -= In.TexCoord.xy; // ピクセルから円の中心へのベクトル
    x = x + 0.1f;
    y = y - 0.001f;
    len.y /= (x /y);

    len = length(len); // ベクトルの長さ
//    if (len.x < 0.1f)  // 長さが0.3未満の場合はモザイク処理
    {
        // モザイク処理
        uv *= float2(x, y); // 画面座標へ変換
        uv /= x; // 配列座標へ変換
        uv = floor(uv) * x; // 矩形の左上座標
        uv /= float2(x, y); // テクスチャ座標へ戻す
 
    }
    outDiffuse = g_Texture.Sample(g_SamplerState, uv); // テクスチャの色を出力
    outDiffuse *= In.Diffuse; // ポリゴンのピクセル色を合成
    
    
    
}
*/


//==================================================
// エントリー関数
//==================================================
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // このピクセルに使うテクセルを取得
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    
    // 乱数作成
    float noise = Rand(In.TexCoord * Parameter.z);
    // 乱数の範囲を調整
    noise = clamp(noise, 0.2f, 0.5f);
    // テクスチャの色へ加算
    outDiffuse.rgb += noise;
    
    // グレースケール化
    {
    // 最終的にoutDiffuse.rgbをYの値にする
    // outDiffuse.aの値は変更しないように注意
    
    //    float Y = 0;
    //    Y = ((0.299 * outDiffuse.r) +
    //     (0.587 * outDiffuse.g) +
    //    (0.114 * outDiffuse.b));
    //    outDiffuse.rgb = Y;
    
    // パターン1
    //    outDiffuse.rgb = ((0.299 * outDiffuse.r) +
    //                       (0.587 * outDiffuse.g) +
    //                        (0.114 * outDiffuse.b));

        // パターン 2
    //   outDiffuse.r = Y;
    //    outDiffuse.g = Y;
    //    outDiffuse.b = Y;

    // パターン3 内積関数を利用する場合
//        float3 sirokuro = float3(0.299f, 0.587f, 0.114f);
 //       outDiffuse.rgb = dot(outDiffuse.rgb, sirokuro);
    
    // Y=0.299*R + 0.587*G + 0.114*B
    }

    // 二乗してみると質感が変わったりする
    outDiffuse.rgb *= outDiffuse.rgb;
    outDiffuse.a = Material.Diffuse.a;
    
    // テクセルの情報にピクセルのデフューズ色を乗算する
    outDiffuse.rgb *= In.Diffuse.rgb;

}
