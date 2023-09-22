#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
#include <Input.h>
#include <PlayerBullet.h>
#include <list>
#include "Sprite.h"

class Player {

public:
	//<summary>
	// 初期化
	//<summary>

	void Initialize(Model* model, uint32_t textureHandle, Vector3 Position);

	/// <summary>
	///  デストラクタ
	/// </summary>
	~Player();

	//<summary>
	// 更新
	//<summary>
	void Update(ViewProjection viewprojection);

	
	//void UpdateUI(ViewProjection viewProjection);

	//<summary>
	// 描画
	////<summary>
	void Draw(ViewProjection& viewprojection);

	/// <summary>
	/// 攻撃
	/// </summary>

	void Attack(Vector3& position);

	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出される関数
	void OnCollision();

	// 弾リスト取得

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	
	

	void SetParent(const WorldTransform* parent);

	

	void DrawUI();

	

private:
	// ワ－ルド変更データ
	WorldTransform worldtransform_;
	ViewProjection viewProjection_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	// 弾

	PlayerBullet* bullet_ = nullptr;

	std::list<PlayerBullet*> bullets_;

	WorldTransform worldTransform3DReticle_;

	//2Dレティクル用のスプライト

	; 
	Sprite* sprite2DReticle_ = nullptr; 
   
	Vector2 ReticlePos_ = {640, 360};

	Vector4 color_ = {1, 1, 1, 1};

	Vector2 anchor_ = {0.5f, 0.5f};

	

};
