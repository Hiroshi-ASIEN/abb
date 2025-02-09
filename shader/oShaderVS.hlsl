
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

  	//���_�ϊ�����
    matrix wvp; //���[���h�r���[�v���W�F�N�V�����s��
    wvp = mul(World, View); //wvp = World�s�� * View�s��
    wvp = mul(wvp, Projection); //wvp = wvp + Projection�s��
    Out.Position = mul(In.Position, wvp); //���_���W��ϊ����ďo��

	//���_�̐F���o��
    Out.Diffuse = In.Diffuse;

	//�e�N�X�`�����W���o��
    Out.TexCoord = In.TexCoord;
}

