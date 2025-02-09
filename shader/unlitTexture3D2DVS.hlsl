
#include "common.hlsl"

StructuredBuffer<float3> Position : register(t2);

void main(in VS_IN In, out PS_IN Out)
{
	
	/*
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
*/	

	// ビルボード用の座標を指定
    Out.Position = mul(In.Position, World);

//    In.Position.xyz += Position[In.InstanceID];
Out.Position.xyz += Position[In.InstanceID];
	
    Out.Position = mul(Out.Position, View);
    Out.Position = mul(Out.Position, Projection);
	
//	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse * Material.Diffuse;

	
	

}

