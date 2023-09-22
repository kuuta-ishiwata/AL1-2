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
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <sstream>

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

	/// <summary>
	///衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 敵弾追加
	/// </summary>
	void AddEnemyBullet(EnemyBullet* enemybullet);
	const std::list<EnemyBullet*>& GetBullets() const { return enemybullets_; }
	
	/// <summary>
	/// 敵発生データの書き込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Sprite* sprite_ = nullptr;

	void EnemySpawn(Vector3& Position);
	void EnemyObjUpdate();
	void EnemyObjDraw();

	//スプライト
	uint32_t textureHandle_ = 0;

	//モデル
	Model* model_ = nullptr;
	Model* modelFighter_ = nullptr;
	//playerカメラ
	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	WorldTransform worldtransform_;

	//enemy
	Enemy* enemy_ = nullptr;
	uint32_t enemytextureHandle_ = 0;
	uint32_t enemybullettectureHandle_ = 0;

	float inputFloat3[3] = {0, 0, 0};

	bool isDebugCameraActive_ = false;
	bool isRailCamera_ = true;
 

	 uint32_t *modelCube_ = nullptr;


	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	
	/// 天球
	Model* Skydomemodel_ = nullptr;

	Skydome* skymodel_ = nullptr; 

	Model* Railcamera_ = nullptr;

	RailCamera* RailCamera_ = nullptr;
	
	Vector3 playerPosition{0.0f, 0.0f, 20.0f};
	Vector3 enemyPosition{0.0f, 0.0f, 20.0f};

	

	std::list<EnemyBullet*> enemybullets_;
	std::list<Enemy*> enemies_;

	//敵発生コマンド
	std::stringstream enemyPopCommands;
	// 待機開始

	// 待機中フラグ
	bool waitflag = true;
	// 待機タイマ
	int32_t waitTimer = 0;

};
