﻿#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
#include <Input.h>
#include <EnemyBullet.h>
#include <list>
#include <player.h>

class Player;


class Enemy
{

public:

	//<summary>
	//初期化
	//<summary>

	void Initialize(Model* model, uint32_t enemytextureHandle);

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
	static const int kFireInverval = 30;

	//接近フェ-ズ初期化
	void Approach();

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	//衝突を検出したら呼び出される関数
	void OnCollision();


	// 弾リスト取得

	const std::list<EnemyBullet*>& GetBullets() const { return enemybullets_; }


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
    //EnemyBullet* enemybullet_ = nullptr;

	std::list<EnemyBullet*> enemybullets_;

	//発射タイマー
	int32_t caunt = 0;

	Player* player_ = nullptr;

	

};

