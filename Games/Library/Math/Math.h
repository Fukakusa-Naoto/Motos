﻿//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file		Math.h
//!
//! @summary	数学関連の関数をまとめたヘッダファイル
//!
//! @date		2018.09.19
//!
//! @author 	深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 =========================================================
#pragma once



// ヘッダファイルの読み込み =======================================================
// <プリコンパイル済みヘッダファイル>
#include "../../pch.h"


// 名前空間の定義 ================================================================
namespace Library
{
	namespace Math
	{
		// 構造体の定義 ==========================================================
		struct Box3D
		{
			// 中心座標
			DirectX::SimpleMath::Vector3 position;
			// サイズ
			DirectX::SimpleMath::Vector3 size;


			// <コンストラクタ>
			Box3D(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& size) :
				position(position),
				size(size)
			{
				// 何もしない
			}
		};


		// 関数の定義 ============================================================
		//------------------------------------------------------------------
		//! @summary   valueを、min から maxの範囲内に収める
		//!
		//! @parameter [value] 制限をかける値
		//! @parameter [min] 最小値
		//! @parameter [max] 最大値
		//!
		//! @return    なし
		//------------------------------------------------------------------
		template<class T> inline void Clamp(T& value, T min, T max)
		{
			if (value <= min) value = min;
			else if (value >= max) value = max;
		}


		//--------------------------------------------------------------
		//! @summary   ピクセル座標を正規化する(ピクセル座標->ワールド座標)
		//!
		//! @parameter [positionX] X座標(ピクセル単位)
		//! @parameter [positionY] Y座標(ピクセル単位)
		//! @parameter [screenWidth] 画面の横幅
		//! @parameter [screenHeight] 画面の高さ
		//!
		//! @return    正規化後の座標
		//--------------------------------------------------------------
		inline DirectX::XMFLOAT3 ConvertPixelToWorld(int positionX, int positionY, int screenWidth, int screenHeight)
		{
			float x = static_cast<float>(positionX) / (static_cast<float>(screenWidth) / 2.0f) - 1.0f;
			float y = -static_cast<float>(positionY) / (static_cast<float>(screenHeight) / 2.0f) + 1.0f;
			return DirectX::XMFLOAT3(x, y, 0.0f);
		}


		//------------------------------------------------------------------
		//! @summary   類似している2つのfloat型の値を比較する
		//!
		//! @parameter [valueA] 数値A
		//! @parameter [valueB] 数値B
		//! @parameter [tolerance] 誤差
		//!
		//! @return    true :等しい
		//! @return    false:等しくない
		//------------------------------------------------------------------
		inline bool Approximately(float valueA, float valueB, float maxRelDiff = FLT_EPSILON)
		{
			// 差を計算する
			float diff = static_cast<float>(fabs(static_cast<double>(valueA) - static_cast<double>(valueB)));
			valueA = static_cast<float>(fabs(static_cast<double>(valueA)));
			valueB = static_cast<float>(fabs(static_cast<double>(valueB)));

			// 最大のものを見つける
			float largest = (valueB > valueA) ? valueB : valueA;

			if (diff <= largest * maxRelDiff) return true;

			return false;
		}



		//------------------------------------------------------------------
		//! @summary   Quaternionをオイラー角に変換する
		//!
		//! @parameter [rotation] 回転角
		//!
		//! @return    オイラー角
		//------------------------------------------------------------------
		inline DirectX::SimpleMath::Vector3 ConvertQuaternionToEulerAngles(const DirectX::SimpleMath::Quaternion& rotation)
		{
			float x = rotation.x;
			float y = rotation.y;
			float z = rotation.z;
			float w = rotation.w;

			float x2 = x * x;
			float y2 = y * y;
			float z2 = z * z;

			float xy = x * y;
			float xz = x * z;
			float yz = y * z;
			float wx = w * x;
			float wy = w * y;
			float wz = w * z;

			// 1 - 2y^2 - 2z^2
			float m00 = 1.0f - (2.0f * y2) - (2.0f * z2);

			// 2xy + 2wz
			float m01 = (2.0f * xy) + (2.0f * wz);

			// 2xy - 2wz
			float m10 = (2.0f * xy) - (2.0f * wz);

			// 1 - 2x^2 - 2z^2
			float m11 = 1.0f - (2.0f * x2) - (2.0f * z2);

			// 2xz + 2wy
			float m20 = (2.0f * xz) + (2.0f * wy);

			// 2yz+2wx
			float m21 = (2.0f * yz) - (2.0f * wx);

			// 1 - 2x^2 - 2y^2
			float m22 = 1.0f - (2.0f * x2) - (2.0f * y2);


			float tx, ty, tz;

			if (Approximately(m21, 1.0f))
			{
				tx = DirectX::XM_PI / 2.0f;
				ty = 0;
				tz = static_cast<float>(atan2(static_cast<double>(m10), static_cast<double>(m00)));
			}
			else if (Approximately(m21, -1.0f))
			{
				tx = -DirectX::XM_PI / 2.0f;
				ty = 0;
				tz = static_cast<float>(atan2(static_cast<float>(m10), static_cast<float>(m00)));
			}
			else
			{
				tx = static_cast<float>(asin(static_cast<float>(-m21)));
				ty = static_cast<float>(atan2(static_cast<float>(m20), static_cast<float>(m22)));
				tz = static_cast<float>(atan2(static_cast<float>(m01), static_cast<float>(m11)));
			}

			return DirectX::SimpleMath::Vector3(DirectX::XMConvertToDegrees(tx), DirectX::XMConvertToDegrees(ty), DirectX::XMConvertToDegrees(tz));
		}


		//------------------------------------------------------------------
		//! @summary   外積を求める
		//!
		//! @parameter [vectorA] ベクトルA
		//! @parameter [vectorB] ベクトルB
		//!
		//! @return    外積
		//------------------------------------------------------------------
		inline const DirectX::SimpleMath::Vector3 Cross(const DirectX::SimpleMath::Vector3& vectorA, const DirectX::SimpleMath::Vector3& vectorB)
		{
			DirectX::SimpleMath::Vector3 tmp;
			tmp.x = vectorA.y * vectorB.z - vectorA.z * vectorB.y;
			tmp.y = vectorA.z * vectorB.x - vectorA.x * vectorB.z;
			tmp.z = vectorA.x * vectorB.y - vectorA.y * vectorB.x;
			return tmp;
		}


		//------------------------------------------------------------------
		//! @summary   クォータニオンの作成
		//!
		//! @parameter [matrix] 行列
		//!
		//! @return    クォータニオン
		//------------------------------------------------------------------
		inline const DirectX::SimpleMath::Quaternion CreateQuaternion(const DirectX::SimpleMath::Matrix& matrix)
		{
			float element[4];
			element[0] = matrix._11 - matrix._22 - matrix._33 + 1.0f;
			element[1] = -matrix._11 + matrix._22 - matrix._33 + 1.0f;
			element[2] = -matrix._11 - matrix._22 + matrix._33 + 1.0f;
			element[3] = matrix._11 + matrix._22 + matrix._33 + 1.0f;

			int biggestIdx = 0;
			for (int i = 0; i < 4; i++)
			{
				if (element[i] > element[biggestIdx])
				{
					biggestIdx = i;
				}
			}

			if (element[biggestIdx] < 0)
			{
				return DirectX::SimpleMath::Quaternion::Identity;
			}

			float q[4];
			float v = static_cast<float>(sqrt(static_cast<float>(element[biggestIdx]))) * 0.5f;
			q[biggestIdx] = v;
			float mult = 0.25f / v;

			switch (biggestIdx)
			{
			case 0:
				q[1] = (matrix._21 + matrix._12) * mult;
				q[2] = (matrix._13 + matrix._31) * mult;
				q[3] = (matrix._32 - matrix._23) * mult;
				break;
			case 1:
				q[0] = (matrix._21 + matrix._12) * mult;
				q[2] = (matrix._32 + matrix._23) * mult;
				q[3] = (matrix._13 - matrix._31) * mult;
				break;
			case 2:
				q[0] = (matrix._13 + matrix._31) * mult;
				q[1] = (matrix._32 + matrix._23) * mult;
				q[3] = (matrix._21 - matrix._12) * mult;
				break;
			case 3:
				q[0] = (matrix._32 - matrix._23) * mult;
				q[1] = (matrix._13 - matrix._31) * mult;
				q[2] = (matrix._21 - matrix._12) * mult;
				break;
			}

			return DirectX::SimpleMath::Quaternion(q[0], q[1], q[2], q[3]);
		}


		inline const DirectX::SimpleMath::Quaternion CreateQuaternion(float yaw, float pitch, float roll)
		{
			float cosRoll = cosf(roll / 2.0f);
			float sinRoll = sinf(roll / 2.0f);
			float cosPitch = cosf(pitch / 2.0f);
			float sinPitch = sinf(pitch / 2.0f);
			float cosYaw = cosf(yaw / 2.0f);
			float sinYaw = sinf(yaw / 2.0f);

			return DirectX::SimpleMath::Quaternion(cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw,
				sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw,
				cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw,
				cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw);
		}


		//------------------------------------------------------------------
		//! @summary   点とボックスの間の最短距離の平方を求める
		//!
		//! @parameter [pointPosition] 点の座標
		//! @parameter [box] ボックスの情報
		//!
		//! @return    最短距離
		//------------------------------------------------------------------
		inline float CalculateShortestRangePointToBox(const DirectX::SimpleMath::Vector3& pointPosition, const Box3D& box)
		{
			float point[3] = { pointPosition.x, pointPosition.y, pointPosition.z };
			float min[3] = { box.position.x - (box.size.x * 0.5f), box.position.y - (box.size.y * 0.5f), box.position.z - (box.size.z * 0.5f), };
			float max[3] = { box.position.x + (box.size.x * 0.5f), box.position.y + (box.size.y * 0.5f), box.position.z + (box.size.z * 0.5f), };

			float shortestRange = 0.0f;
			for (int i = 0; i < 3; i++)
			{
				float v = point[i];
				if (v < min[i]) shortestRange += (min[i] - v) * (min[i] - v);
				if (v > max[i]) shortestRange += (v - max[i]) * (v - max[i]);
			}
			return shortestRange;
		}
	}
}