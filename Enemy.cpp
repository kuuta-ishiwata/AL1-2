#include "Enemy.h"
#include "EnemyBullet.h"
#include "MATHEX.h"
#include "player.h"
#include <ImGuiManager.h>
#include <assert.h>
#include "GameScene.h"

Enemy::~Enemy() {
	//// 敵弾解放
	//for (EnemyBullet* enemybullet : enemybullets_) {
	//
	//	delete enemybullet;
	//}
}

void Enemy::Initialize(Model* model, uint32_t enemytextureHandle, Vector3 Position) {

	assert(model);
	model_ = model;
	enemytextureHandle_ = enemytextureHandle;

	worldtransform_.Initialize();
	 
	worldtransform_.translation_ = {10.0f, 10.0f, 10.0f};

	worldtransform_.translation_ = Position;

	Approach();

}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	//  ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
	
}

void Enemy::OnCollision() 
{ isdead_ =  true; }



void Enemy::Approach() {

	// 発射タイマーを初期化
	count = kFireInverval;
}

void Enemy::Fire(Vector3& position) {

	assert(player_);

	// 弾速度
	const float kenemybulletspeed = 0.3f;
	Vector3 enemyvelocity(kenemybulletspeed, kenemybulletspeed, kenemybulletspeed);

	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enemyPos = GetWorldPosition();

	Vector3 Result = {

	    playerPos.x - enemyPos.x, playerPos.y - enemyPos.y, playerPos.z - enemyPos.z

	};

	Vector3 ResultNomalize = Normalize(Result);

	enemyvelocity = {


	    ResultNomalize.x * enemyvelocity.x, ResultNomalize.y * enemyvelocity.y,
	    ResultNomalize.z * enemyvelocity.z


	};

	// 敵弾解放

	/*
	if (enemybullets_)
	{

	    delete enemybullets_;
	    enemybullets_ = nullptr;

	}
	*/

	/// 敵の弾を生成し初期化
	EnemyBullet* newEnemybulet = new EnemyBullet();
	newEnemybulet->Initialize(model_, position, enemyvelocity);

	gameScene_->AddEnemyBullet(newEnemybulet);

	// 弾登録
	//enemybullets_.push_back(newEnemybulet);


	// Approach();

}

void Enemy::Update() {

	const float kenemyspeed = 0.2f;
	Vector3 move = {0, 0, 0};
	switch (phase_) {

	case Phase::Approach:
	default:
		count--;

		// 移動（ベクトル加算）
		worldtransform_.translation_.z -= kenemyspeed;

		// 規定の位置に到達したら離脱
		
		if (worldtransform_.translation_.z < 0.0f) 
		{
			worldtransform_.translation_.z = 0;
		
		
		}
		
		if (count <= 0) {

			// 敵攻撃
			Fire(worldtransform_.translation_);

			// 発射タイマーを初期化
			count = kFireInverval;

		}

		break;
	case Phase::Leave:

		// 移動ベクトルの加算
		worldtransform_.translation_.y += kenemyspeed;
		worldtransform_.translation_.x -= kenemyspeed;

		break;
	}

	worldtransform_.UpdateMatrix();

	// デスフラグの立った弾を削除
	/*enemybullets_.remove_if([](EnemyBullet* enemybullet) {
		if (enemybullet->IsDead()) {
			delete enemybullet;
			return true;
		}
		return false;
	});*/

	worldtransform_.TransferMatrix();
	/*for (EnemyBullet* enemybullet : enemybullets_) {

		enemybullet->Update();
	}*/
}

void Enemy::Draw(ViewProjection& enemyviewprojection) {


	if (isdead_ == false)
	{
		model_->Draw(worldtransform_, enemyviewprojection, enemytextureHandle_);
	}

	// 敵弾描画
	//for(EnemyBullet* enemybullet : enemybullets) {
	//	enemybullet->Draw(enemyviewprojection);
	//}

}