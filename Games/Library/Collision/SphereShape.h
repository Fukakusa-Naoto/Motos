﻿//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file		SphereShape.h
//!
//! @summary	球状衝突判定クラスのヘッダファイル
//!
//! @date		2018.11.26
//!
//! @author		深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 =========================================================
#pragma once



// ヘッダファイルの読み込み =======================================================
// <自作ヘッダファイル>
#include "CollisionShape.h"


// 名前空間の定義 ================================================================
namespace Library
{
	namespace Collision
	{
		// クラスの定義 ==========================================================
		class SphereShape : public CollisionShape
		{
			// <メンバ変数>
		private:
			// 半径
			float m_radius;


			// <コンストラクタ>
		public:
			//--------------------------------------------------------------
			//! @parameter [controller] 制御コンポーネント
			//! @parameter [transform] 座標変換コンポーネント
			//! @parameter [radius] 半径
			//--------------------------------------------------------------
			SphereShape(System::ControllerBase* controller, Math::Transform& transform, float radius);


			// <デストラクタ>
		public:
			~SphereShape();


			// <ゲッター関数>
		public:
			//--------------------------------------------------------------
			//! @summary   半径の取得
			//--------------------------------------------------------------
			inline float GetRadius() const { return m_radius; }
		};
	}
}
