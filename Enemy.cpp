#include "Enemy.h"
#include "EnemyBullet.h"
#include "MATHEX.h"
#include "player.h"
#include <ImGuiManager.h>
#include <assert.h>

Enemy::~Enemy() {
	// 敵弾解放
	for (EnemyBullet* enemybullet : enemybullets_) {

		delete enemybullet;
	}
}

void Enemy::Initialize(Model* model, uint32_t enemytextureHandle) {

	assert(model);
	model_ = model;
	enemytextureHandle_ = enemytextureHandle;

	worldtransform_.Initialize();

	worldtransform_.translation_ = {5.0f, 2.0f, 50.0f};

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

void Enemy::OnCollision() {}

void Enemy::Approach() {

	// 発射タイマーを初期化
	caunt = kFireInverval;
}

void Enemy::Fire(Vector3& position) {

	assert(player_);

	// 弾速度
	const float kenemybulletspeed = 0.5f;

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

	// 弾登録
	enemybullets_.push_back(newEnemybulet);


	// Approach();

}

void Enemy::Update() {

	const float kenemyspeed = 0.2f;
	Vector3 move = {0, 0, 0};
	switch (phase_) {

	case Phase::Approach:
	default:
		caunt--;

		// 移動（ベクトル加算）
		worldtransform_.translation_.z -= kenemyspeed;

		// 規定の位置に到達したら離脱

		if (worldtransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}

		if (caunt <= 0) {

			// 敵攻撃
			Fire(worldtransform_.translation_);

			// 発射タイマーを初期化
			caunt = kFireInverval;
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
	enemybullets_.remove_if([](EnemyBullet* enemybullet) {
		if (enemybullet->IsDead()) {
			delete enemybullet;
			return true;
		}
		return false;
	});

	worldtransform_.UpdateMatrix();

	for (EnemyBullet* enemybullet : enemybullets_) {

		enemybullet->Update();
	}
}

void Enemy::Draw(ViewProjection& enemyviewprojection) {

	model_->Draw(worldtransform_, enemyviewprojection, enemytextureHandle_);

	// 敵弾描画
	for (EnemyBullet* enemybullet : enemybullets_) {
		enemybullet->Draw(enemyviewprojection);
	}
}