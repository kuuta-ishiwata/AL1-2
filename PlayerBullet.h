#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include<assert.h>
#include <Input.h>
#include "Model.h"



class PlayerBullet {

public:
	///< summary>
	/// 初期化
	///  </summary>
	///  <param name= "model">モデル</param>
	///  <param name = "position">初期化座標</param>

	void Initialize(Model* model, const Vector3& position, const Vector3 velocity);

	///< summary>
	/// 更新
	///  </summary>
	void Update();
	// 寿命
	static const int32_t kLifeTime = 60 * 5;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;

	bool IsDead() const { return isDead_; }

	///< summary>
	// 描画
	///</summary>
	///< param name="viewProjection">ビュープロジェクション</param>

	void Draw(const ViewProjection& viewprojection);

	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出される関数
	void OnCollision();

	

private:
	// ワールド変更データ
	WorldTransform worldtransform_;
	ViewProjection viewProjection_;
	// モデルのポインタ
	Model* model_ = nullptr;

	// テクスチャハンドル

	uint32_t bullettextureHandle_ = 0u;
	Input* input_ = nullptr;

	// 速度
	Vector3 velocity_ = {0, 0, 0.5f};

	
	
};
