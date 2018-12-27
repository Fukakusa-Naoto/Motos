﻿//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file		GameObject.h
//!
//! @summary	ゲームオブジェクトの基底クラスのヘッダファイル
//!
//! @date		2018.12.06
//!
//! @author		深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 =========================================================
#pragma once



// ヘッダファイルの読み込み =======================================================
// <自作ヘッダーファイル>
#include "../Math/Transform.h"


// 名前空間の定義 ================================================================
namespace Library
{
	// クラスの宣言 ==============================================================
	namespace Common { class StepTimer; }
	namespace Camera { class Camera; }

	namespace System
	{
		// コントローラーの基底クラス
		class ControllerBase;


		// クラスの定義 ==========================================================
		class GameObject
		{
			// <メンバ変数>
		protected:
			// カメラ
			Library::Camera::Camera* m_camera;
			// 座標変換コンポーネント
			Library::Math::Transform m_transform;
			// 制御
			ControllerBase* m_controller;
			// タグ
			unsigned int m_tag;


			// <コンストラクタ>
		public:
			//--------------------------------------------------------------
			//! @parameter [void] なし
			//--------------------------------------------------------------
			GameObject();


			// <デストラクタ>
		public:
			virtual ~GameObject();


			// <メンバ関数>
		public:
			//--------------------------------------------------------------
			//! @summary   初期化処理
			//!
			//! @parameter [void] なし
			//!
			//! @return    なし
			//--------------------------------------------------------------
			virtual void Start() = 0;


			//--------------------------------------------------------------
			//! @summary   更新処理
			//!
			//! @parameter [timer] 時間情報
			//!
			//! @return    なし
			//--------------------------------------------------------------
			virtual void Update(const Library::Common::StepTimer & timer) = 0;



			//--------------------------------------------------------------
			//! @summary   描画処理
			//!
			//! @parameter [void] なし
			//!
			//! @return    なし
			//--------------------------------------------------------------
			virtual void Draw() = 0;


			// <セッター関数>
		public:
			//--------------------------------------------------------------
			//! @parameter [camera] カメラ
			//--------------------------------------------------------------
			inline void SetCamera(Library::Camera::Camera* camera) { m_camera = camera; }


			// <ゲッター関数>
		public:
			//--------------------------------------------------------------
			//! @summary   タグの取得
			//--------------------------------------------------------------
			inline unsigned int GetTag() const { return m_tag; }


			//--------------------------------------------------------------
			//! @summary   座標変換コンポーネントの取得
			//--------------------------------------------------------------
			inline const Math::Transform& GetTransform() const { return m_transform; }
		};
	}
}
