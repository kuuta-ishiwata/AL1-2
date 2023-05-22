#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
	
	//自キャラr
	//player* player_ = nullptr;

	float inputFloat3[3] = {0, 0, 0};

	bool isDebugCameraActive_ = false; 

	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();


	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Sprite* sprite_ = nullptr;
	//スプライト
	uint32_t textureHandle_ = 0;
	//モデル
	Model* model_;
	//カメラ
	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	WorldTransform worldtransform_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
