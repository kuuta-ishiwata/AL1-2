#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
#include <Input.h>
#include <EnemyBullet.h>
#include <list>
#include <player.h>

class Player;

// GameSceneの前方宣言
class GameScene;

class Enemy
{

public:


	//<summary>
	//初期化
	//<summary>

	void Initialize(Model* model, uint32_t enemytextureHandle, Vector3 Position);

	///<summary>
	///デストラクタ
	/// <summary>
	~Enemy();

	///<summary>
	/// 更新
	///<summary>
	void Update();
	
    ///<symmary>
	///描画
	/// <summary>
	void Draw(ViewProjection& enemyviewprojection);


	///< summary>
	/// 弾発射
	///< summary>

	void Fire(Vector3& position);

	//発射間隔
	static const int kFireInverval = 90;

	//接近フェ-ズ初期化
	void Approach();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	//衝突を検出したら呼び出される関数
	void OnCollision();
	void OnCollision2();
	//const std::list<EnemyBullet*>& EnemyGetBullets() const { return Enemybullets_; }

	// 弾リスト取得


	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	bool IsDead() const 
	{ 
		
		return isdead_;


	}

private:
	enum class Phase 
	{

		Approach, // 接近する
		Leave,    // 離脱する
	};

	WorldTransform worldtransform_;
	ViewProjection enemyviewprojection_;

	Model* model_ = nullptr;

	uint32_t enemytextureHandle_ = 0u;

	Input* input_ = nullptr;

	
	Phase phase_ = Phase::Approach;
	
	//敵弾
   
	std::list<EnemyBullet*> Enemybullets_;


	//発射タイマー
	int32_t count = 0;

	Player* player_ = nullptr;

	//ゲームシーン
	GameScene* gameScene_ = nullptr;

	bool isdead_ = false;
	bool isdead2_ = false;

};

