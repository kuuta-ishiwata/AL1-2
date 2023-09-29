#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <Input.h>
#include <assert.h>

class EnemyBullet {

public:
	///< summary>
	/// 初期化
	///  <summary>
	///  <param name= "model">モデル</param>
	///  <param name = "position">初期化座標</param>

	void Initialize(Model* model, const Vector3& Enemybulletposition, const Vector3 velocity);

	///< summary>
	/// 更新
	/// </summary>
	void Update();

	bool IsDead() const { return isDead_; }
	///< summary>
	// 描画
	///</summary>
	///< param name="viewProjection">ビュープロジェクション</param>

	void Draw(const ViewProjection& viewprojection);

	// 衝突を検出したら呼び出される関数
	void OnCollision();

	
	Vector3 GetWorldPosition();

	


private:

	
	// 寿命
	static const int32_t kLifeTime = 60 * 5;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
	// ワールド変更データ
	WorldTransform worldtransform_;
	ViewProjection viewProjection_;
	// モデルのポインタ
	Model* model_ = nullptr;

	// テクスチャハンドル

	uint32_t enemybullettextureHandle_ = 0u;

	
	// 速度
	Vector3 enemybulltvelocity_ = {0.0f,0.0f,0.2f};

	

};
