#include "GameScene.h"
#include "TextureManager.h"
#include "PrimitiveDrawer.h"
#include <cassert>
#include "ImGuiManager.h"
#include "AxisIndicator.h"
#include "player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"



GameScene::GameScene() 
{
	
	

}


GameScene::~GameScene() 
{

	// デストラクタ
	delete sprite_;
	delete player_;
	delete model_;
	delete enemy_;
	
}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("ga.png");
	enemytextureHandle_ = TextureManager::Load("white1x1.png");

	// モデル

	worldtransform_.Initialize();

	viewProjection_.Initialize();
	model_ = Model::Create();
	// sprite_ = Sprite::Create(textureHandle_, {350, 20});
	//  自キャラの編成
	player_ = new Player();

	enemy_ = new Enemy();
	
	
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);
	
	enemy_->SetPlayer(player_);


	//敵キャラ初期化
	enemy_->Initialize(model_, enemytextureHandle_); 

	
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);


}



void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
		const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	    const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region // 自キャラ敵弾当たり判定

	// 自キャラ座標
	posA = player_->GetWorldPosition();

	// 自キャラの敵弾当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		float  radius = 0.7f;
	
		float px;
		float py;
		float pz;
		
		px = posB.x - posA.x;
		py = posB.y - posA.y;
		pz = posB.z - posA.z;

		
		float Pos;

		Pos = (px * px) + (py * py) + (pz * pz);

		if (Pos <= (radius + radius) * (radius + radius)) {

			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

	

	Vector3 PosB, PosA;
	// 敵キャラ座標
	PosB = enemy_->GetWorldPosition();

	for (PlayerBullet* playerbullet : playerBullets)
	{

		PosA =  playerbullet->GetWorldPosition();

		float radius2 = 0.7f;

		float Px;
		float Py;
		float Pz;

		Px = PosA.x - PosB.x;
		Py = PosA.y - PosB.y;
		Pz = PosA.z - PosB.z;

		float Pos2;

		Pos2 = (Px * Px) + (Py * Py) + (Pz * Pz);

		if (Pos2 <= (radius2 + radius2) * (radius2 + radius2)) 
		{

			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			playerbullet->OnCollision();

		}
	}


	Vector3 POSA, POSB;
	
	for (PlayerBullet* playerbullet : playerBullets)
	{
		POSA = playerbullet->GetWorldPosition();

		for (EnemyBullet* enemybullet : enemyBullets)
		{
			
			POSB = enemybullet->GetWorldPosition();

			float radius3 = 0.7f;

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


void GameScene::Update() { 
	// 自キャラの更新
	player_->Update();

	/*
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	*/

	//敵キャラ
	enemy_->Update();
	
	CheckAllCollisions();
	
	

#ifdef  _DEBUG

	if (input_->TriggerKey(DIK_M))
	{
		isDebugCameraActive_ = true;
    }

#endif //  

	if (isDebugCameraActive_) 
	{
		debugCamera_->Update();	
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	
	} else {
	
	//ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();

	}

}

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
	
	player_->Draw(viewProjection_);

    enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理

	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();
	// スプライト描画後処理
	 Sprite::PostDraw();

#pragma endregion
}
