#include "GameScene.h"
#include "AxisIndicator.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "ImGuiManager.h"
#include "PlayerBullet.h"
#include "PrimitiveDrawer.h"
#include "RailCamera.h"
#include "Scene.h"
#include "Skydome.h"
#include "TextureManager.h"
#include "Title.h"
#include "player.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ
	delete sprite_;
	delete player_;
	delete model_;
	delete enemy_;
	delete Skydomemodel_;
	delete Railcamera_;

	// 敵弾解放
	for (EnemyBullet* enemybullet : enemybullets_) {
		delete enemybullet;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("ga.png");
	enemytextureHandle_ = TextureManager::Load("white1x1.png");
	Skydomemodel_ = Model::CreateFromOBJ("skydome", true);

	// レティクルのテクスチャ
	TextureManager::Load("aim.png");

	// TextureManager::Load("clear.png");
	// TextureManager::Load("gameover.png");
	// TextureManager::Load("start.png");

	Vector3 radian{0, 0, 0};

	// Vector3 playerPosition{0.0f, 0.0f, 20.0f};
	// Vector3 enemyPosition{0, 10, 50};

	// モデル
	worldtransform_.Initialize();

	viewProjection_.Initialize();
	model_ = Model::Create();
	// sprite_ = Sprite::Create(textureHandle_, {350, 20});
	//  自キャラの編成
	player_ = new Player();

	enemy_ = new Enemy();

	// 自キャラの初期化
	// 引数
	player_->Initialize(model_, textureHandle_, {0.0f, 0.0f, 15.0f});

	enemy_->SetPlayer(player_);

	// 敵キャラ初期化
	enemy_->Initialize(model_, enemytextureHandle_, enemyPosition);

	enemy_->SetGameScene(this);

	// 天球
	skymodel_ = new Skydome();

	skymodel_->Initialize(Skydomemodel_);

	viewProjection_.farZ = 1000.0f;

	// レールカメラ

	RailCamera_ = new RailCamera();

	RailCamera_->Initialize({0.0f, 0.0f, -50.0f});

	player_->SetParent(&RailCamera_->GetworldTransform());

	LoadEnemyPopData();

	//->Initialize(model_, textureHandle_ ,playerPosition);

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_M)) {
		isDebugCameraActive_ = true;
	}

#endif //

	// デバッグ
	if (isDebugCameraActive_) {

		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

	} else {
		// ゲームカメラ
		// ビュープロジェクション行列の更新と転送
		// viewProjection_.UpdateMatrix();
		RailCamera_->Update();
		viewProjection_.matView = RailCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = RailCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}

	// 自キャラの更新
	player_->Update(viewProjection_);

	/*
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	*/

	// 敵キャラ
	// enemy_->Update();
	UpdateEnemyPopCommands();

	skymodel_->Update();

	RailCamera_->Update();

	EnemyObjUpdate();

	CheckAllCollisions();

	player_->Update(viewProjection_);

	// シーン切り替え

	//	スクリーン切り替え

	if (count2 == 1) {

		isSceneEnd = true;
	}

	if (count >= 11) {

		isSceneEnd2 = true;
	}
}

void GameScene::Reset() {

	isSceneEnd = false;

	count2 = 0;

	player_->Initialize(model_, textureHandle_, playerPosition);

	// if (isSceneEnd) {
	//	return;
	// }

	enemies_.clear();
	enemybullets_.clear();
	enemyPopCommands.clear();
	LoadEnemyPopData();
	return;

	// if (isSceneEnd == true)
	//{
	//	Vector3 playerPosition = {0, 0, 20};
	//	player_->Initialize(model_, textureHandle_, playerPosition);
	//
	// }
}

void GameScene::Reset2() {

	isSceneEnd2 = false;

	count = 0;
}

void GameScene::Restart() {}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

#pragma endregion

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	skymodel_->Draw(viewProjection_);

	player_->Draw(viewProjection_);

	// enemy_->Draw(viewProjection_);

	EnemyObjDraw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理

	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// sprite_->Draw();

	player_->DrawUI();

	//  スプライト描画後処理
	Sprite::PostDraw();
}

void GameScene::AddEnemyBullet(EnemyBullet* enemybullet) {

	// リスト登録
	enemybullets_.push_back(enemybullet);
}

void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標

	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	//// 敵弾リストの取得
	// const std::list<EnemyBullet*>& enemyBullets = enemy_->Get();

#pragma region // 自キャラ敵弾当たり判定

	// 自キャラ座標
	posA = player_->GetWorldPosition();

	// 自キャラの敵弾当たり判定
	for (EnemyBullet* bullet : enemybullets_) {

		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		float radius = 2.0f;

		float px;
		float py;
		float pz;

		px = posB.x - posA.x;
		py = posB.y - posA.y;
		pz = posB.z - posA.z;

		float Pos;

		Pos = (px * px) + (py * py) + (pz * pz);

		if (Pos <= (radius * radius) + (radius * radius)) {

			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();

			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();

			count2 += 1;
		}
	}

	Vector3 posC, posD;

	// 敵キャラ

	for (PlayerBullet* bullet : playerBullets) {

		posD = bullet->GetWorldPosition();

		for (Enemy* Enemies : enemies_) {

			posC = Enemies->GetWorldPosition();

			float radius = 1.5f;

			float px;
			float py;
			float pz;

			px = posD.x - posC.x;
			py = posD.y - posC.y;
			pz = posD.z - posC.z;

			float Pos;

			Pos = (px * px) + (py * py) + (pz * pz);

			if (Pos <= (radius * radius) + (radius * radius)) {

				// 自キャラの衝突時コールバックを呼び出す
				enemy_->OnCollision();

				// 敵弾の衝突時コールバックを呼び出す
				bullet->OnCollision();

				Enemies->OnCollision();
				count += 1;
				// enemybulles_->OnCollision();
			}

			// if (count == 1)
			//{
			//	count = 0;
			// }
		}
	}

	Vector3 POSA, POSB;

	for (PlayerBullet* playerbullet : playerBullets) {

		POSA = playerbullet->GetWorldPosition();

		for (EnemyBullet* enemybullet : enemybullets_) {

			POSB = enemybullet->GetWorldPosition();

			float radius3 = 1.0f;

			float PX;
			float PY;
			float PZ;

			PX = POSA.x - POSB.x;
			PY = POSA.y - POSB.y;
			PZ = POSA.z - POSB.z;

			float POS;

			POS = (PX * PX) + (PY * PY) + (PZ * PZ);

			if (POS <= (radius3 + radius3) * (radius3 + radius3)) {

				// 敵玉の衝突時コールバックを呼び出す
				playerbullet->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
				enemybullet->OnCollision();
			}
		}
	}
}

void GameScene::EnemySpawn() {

	Enemy* enemy = new Enemy;

	enemy->Initialize(model_, enemytextureHandle_, enemyPosition);

	enemy->SetPlayer(player_);

	enemy->SetGameScene(this);

	enemies_.push_back(enemy);
}

void GameScene::EnemyObjUpdate() {

	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	enemies_.remove_if([](Enemy* enemy_) {
		if (enemy_->IsDead()) {
			delete enemy_;
			return true;
		}
		return false;
	});

	for (EnemyBullet* enemybullet : enemybullets_) {

		enemybullet->Update();
	}

	// デスフラグの立った弾を削除
	enemybullets_.remove_if([](EnemyBullet* enemybullet) {
		if (enemybullet->IsDead()) {
			delete enemybullet;
			return true;
		}
		return false;
	});
}

void GameScene::EnemyObjDraw() {

	for (Enemy* enemy : enemies_) {

		enemy->Draw(viewProjection_);
	}

	// 敵弾描画

	for (EnemyBullet* enemybullet : enemybullets_) {

		enemybullet->Draw(viewProjection_);
	}
}

void GameScene::LoadEnemyPopData() {

	// ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {

	// 待機処理
	if (waitflag) {

		waitTimer--;
		if (waitTimer <= 0) {
			waitflag = false;
		}
		return;
	}

	// 1行列分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// 区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}

		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる

			enemyPosition = {x, y, z};

			EnemySpawn();

		}

		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			waitflag = true;
			waitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}