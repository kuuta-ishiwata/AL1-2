#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
#include <Input.h>
#include<PlayerBullet.h>
#include <list>
#define _USE_MATH_DEFINES

class Player {

public:

	//<summary>
	// 初期化
	//<summary>

	Vector3 GetWorldPosition();

    const WorldTransform& GetworldTransform() const { return worldtransform_; }

	//void Initialize(Model* model, uint32_t textureHandle);
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm_, Model* modelR_arm);


	void SetViewProjection(const ViewProjection* viewprojection) {
		viewprojection_ = viewprojection;
	}
	/// <summary>
	///  デストラクタ
	///// </summary>
	//Player();
	//~Player(){};
	
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

	//void Attack(Vector3 &position);
	//浮遊
	void InitializeFloatingGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();


private:

	// ワ－ルド変更データ
	WorldTransform worldtransform_;
	const ViewProjection* viewprojection_ = nullptr;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	//uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	
	//弾
	// PlayerBullet* bullet_ = nullptr;
	
	//std::list<PlayerBullet*> bullets_;

	Model* modelFighterBody_;
	Model* modelFighterhead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	WorldTransform WorldTransformBody;
	WorldTransform WorldTransformHead;
	WorldTransform WorldTransformL_arm;
	WorldTransform WorldTransformR_arm;

	float floatingParameter_ = 0.0f;


};
