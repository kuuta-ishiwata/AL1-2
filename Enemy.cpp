#include <assert.h>
#include <ImGuiManager.h>
#include "Enemy.h"
#include "MATHEX.h"
#include "EnemyBullet.h"


Enemy::~Enemy(){
	// 敵弾解放
	for (EnemyBullet* enemybullet : enemybullets_) 
{

		delete enemybullet;

	}
}



void Enemy::Initialize(Model* model, uint32_t enemytextureHandle)
{ 

	assert(model);
	model_ = model;
	enemytextureHandle_ = enemytextureHandle;

	worldtransform_.Initialize();
	
	worldtransform_.translation_ = {20.0f, 2.0f, 20.0f};
	
	Approach();
     
}

void Enemy::Approach()
{

	// 発射タイマーを初期化
	caunt = kFireInverval;
					
	
}


void Enemy::Fire(Vector3& position)
{
		
	// 弾速度
	const float kenemybulletspeed = -0.5f;
	Vector3 enemyvelocity(0, 0, kenemybulletspeed);

	//敵弾解放
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

	//弾登録
	enemybullets_.push_back(newEnemybulet);
	
	//Approach();

}


void Enemy::Update() 
{	
	
	const float kenemyspeed = 0.2f;
	Vector3 move = {0, 0, 0};
	switch (phase_) 
	{

	case Phase::Approach:
	default:
		caunt--;


		// 移動（ベクトル加算）
		worldtransform_.translation_.z -= kenemyspeed;

		// 規定の位置に到達したら離脱

		if (worldtransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		
		if (caunt <= 0)
		{
		
			// 敵攻撃
			Fire(worldtransform_.translation_);

			// 発射タイマーを初期化
			caunt = kFireInverval;
		}

		
		break;
	case Phase::Leave:


		//移動ベクトルの加算
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


void Enemy::Draw(ViewProjection& enemyviewprojection)
{


	model_->Draw(worldtransform_, enemyviewprojection, enemytextureHandle_);


	//敵弾描画
	for (EnemyBullet* enemybullet : enemybullets_) 
	{
		enemybullet->Draw(enemyviewprojection);
	}


}