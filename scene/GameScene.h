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
#include "PlayerBullet.h"
#include <memory>
#include "Skydome.h"
#include "Ground.h"
#include "RailCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

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
	//Model* model_ = nullptr;
	std::unique_ptr<Model> model_;
	std::unique_ptr<Model> skydomemodel_;
	std::unique_ptr<Model> groundmodel_;

	std::unique_ptr<Model> railcamera_;


	//Player* player_ = nullptr;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<RailCamera> Railcamera_;

	WorldTransform worldtransform_;

	
	ViewProjection viewProjection_;

	


	float inputFloat3[3] = {0, 0, 0};

	bool isDebugCameraActive_ = false;

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>

	 
 
	
};
