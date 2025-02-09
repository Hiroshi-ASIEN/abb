
//common2.hlsl


//C言語から受け取る情報を格納する変数
//コンスタントバッファの内容がここに入る

cbuffer		WorldBuffer : register(b0)//定数バッファ0番
{
	matrix	World;	//ワールド行列
}

cbuffer ViewBuffer : register(b1)//定数バッファ1番
{
	matrix	View;	//カメラ行列
}

cbuffer ProjectionBuffer : register(b2)//定数バッファ2番
{
	matrix	Projection;	//プロジェクション行列
}

//頂点のデータ構造体
struct VS_IN
{
	float4		Position	: POSITION0;//ポジションゼロ
	float4		Normal		: NORMAL0;	//ノーマルゼロ
	float4		Diffuse		: COLOR0;	//カラーゼロ
	float2		TexCoord	: TEXCOORD0;	//テクスコードゼロ
};//表示するポリゴンの頂点レイアウトと同じ

//ピクセルシェーダーへ入力されるピクセル情報
struct PS_IN
{
	float4		Position		: SV_POSITION;	//ピクセルの画面座標
	float4		WorldPosition	: POSITION0;	//ピクセルの空間での座標
	float4		Normal			: NORMAL0;		//ピクセルの法線
	float4		Diffuse			: COLOR0;		//ピクセルの色
	float2		TexCoord		: TEXCOORD0;	//ピクセルのテクスチャ座標
};

//ライト構造体の定義　C言語側のLIGHT構造体と同じ内容
struct LIGHT
{
	bool	Enable;//bool型だがfloat型でうまくやってくれている
	bool3	Dummy;
	float4	Direction;
	float4	Diffuse;
	float4	Ambient;
	
    float4 SkyColor;		// 天球色
    float4 GroundColor;		// 地面色
    float4 GroundNormal;	// 地面法線
	
    float4 Position;		// 座標
    float4 PointParam;		// 光の範囲
};
cbuffer		LightBuffer : register(b4)//コンスタントバッファ４番で受け取る
{
	LIGHT	Light;	//ライト型構造体として利用する
}

cbuffer CameraBuffer : register(b5)	//バッファ5番
{
	float4	CameraPosition;	//カメラの座標
}


//==================================================
// 汎用パラメーター受け取り用
//==================================================
cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter;	//  C言語側から何か受け取る
	
	
}

//////////////////EOF////////////////////////////////////////////






