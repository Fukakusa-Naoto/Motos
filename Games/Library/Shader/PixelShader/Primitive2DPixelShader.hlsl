#include "../Header/Primitive2D.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
    // 色を出力する
    return input.color;
}