﻿//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file		EnemyManager.cpp
//!
//! @summary	モトスの敵管理クラスのソースファイル
//!
//! @date		2018.12.10
//!
//! @author		深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み =================================================
// <プリコンパイル済みヘッダファイル>
#include "../../pch.h"

// <自作ヘッダーファイル>
#include "EnemyManager.h"
#include "TaskManager.h"
#include "../Play/Object/Enemy/Enemy.h"
#include "../Play/Object/Stage/Tile.h"


// usingディレクティブ =====================================================
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Library;


// 関数の定義 ==============================================================
//--------------------------------------------------------------------
//! @summary   コンストラクタ
//!
//! @parameter [void] なし
//--------------------------------------------------------------------
Motos::Utility::EnemyManager::EnemyManager() :
	m_enemyCount(0)
{
	// 何もしない
}



//--------------------------------------------------------------------
//! @summary   デストラクタ
//!
//! @parameter [void] なし
//--------------------------------------------------------------------
Motos::Utility::EnemyManager::~EnemyManager()
{
	if (m_enemyList.size() != 0)
	{
		for (list<Play::Object::Enemy::Enemy*>::iterator itr = m_enemyList.begin(); itr != m_enemyList.end(); ++itr)
		{
			delete (*itr);
		}
	}

	m_enemyList.clear();
}



//--------------------------------------------------------------------
//! @summary   敵の作成処理
//!
//! @parameter [objectData] オブジェクトデータ
//! @parameter [camera] カメラ
//! @parameter [taskManager] タスクマネージャー
//! @parameter [target] ターゲットの情報
//!
//! @return    なし
//--------------------------------------------------------------------
void Motos::Utility::EnemyManager::Create(vector<int>& objectData, Library::Camera::Camera* camera, TaskManager* taskManager, System::GameObject* target)
{
	for (unsigned int i = 0; i < objectData.size(); ++i)
	{
		switch (objectData[i])
		{
		case 2:
		{
			Play::Object::Enemy::Enemy* enemy = new Play::Object::Enemy::Enemy();
			enemy->SetCamera(camera);
			enemy->SetTartet(target);
			enemy->SetEnemyManager(this);

			float x = static_cast<float>(i % 12) - 6.0f;
			float z = static_cast<float>(i / 12) - 6.0f;
			enemy->SetPosition(Vector3(x, 0.5f, z));

			taskManager->Entry(enemy);
			m_enemyList.push_back(enemy);

			++m_enemyCount;
		}
		break;
		default:
			break;
		}
	}
}



//--------------------------------------------------------------------
//! @summary   現在生存している敵の数を減らす
//!
//! @parameter [void] なし
//!
//! @return    なし
//--------------------------------------------------------------------
void Motos::Utility::EnemyManager::SubCount()
{
	--m_enemyCount;
}
