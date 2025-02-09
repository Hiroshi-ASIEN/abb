
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

  	//頂点変換処理
    matrix wvp; //ワールドビュープロジェクション行列
    wvp = mul(World, View); //wvp = World行列 * View行列
    wvp = mul(wvp, Projection); //wvp = wvp + Projection行列
    Out.Position = mul(In.Position, wvp); //頂点座標を変換して出力

	//頂点の色を出力
    Out.Diffuse = In.Diffuse;

	//テクスチャ座標を出力
    Out.TexCoord = In.TexCoord;
}

