#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
#include <Input.h>
#include <PlayerBullet.h>
#include <list>


class Player {

public:
	//<summary>
	// 初期化
	//<summary>

	void Initialize(Model* model, uint32_t textureHandle);


	/// <summary>
	///  デストラクタ
	/// </summary>
	~Player(){};

	//<summary>
	// 更新
	//<summary>
	void Update();
	


	//<summary>
	// 描画
	////<summary>
	void Draw(ViewProjection& viewprojection);

/// <summary>
/// 攻撃
/// </summary>

	void Attack(Vector3 &position);


	


private:
	// ワ－ルド変更データ
	WorldTransform worldtransform_;
	ViewProjection viewProjection_;
	Vector3 GetWorldposition();
	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;


	//uint32_t* position_ = nullptr;


	//弾

	 PlayerBullet* bullet_ = nullptr;
	
	std::list<PlayerBullet*> bullets_;

	


};
