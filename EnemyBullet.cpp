#include "MATHEX.h"
#include "EnemyBullet.h"
#include "WorldTransform.h"
#include <ImGuiManager.h>
#include <assert.h>


void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3 enemybulletvelocity)
{

	assert(model);
	model_ = model;
	//テクスチャ読み
	enemybullettextureHandle_ = TextureManager::Load("sample.png");

	worldtransform_.Initialize();
	worldtransform_.translation_ = position;

	enemybulltvelocity_ = enemybulletvelocity;

}


void EnemyBullet::Update() 
{
	
	worldtransform_.UpdateMatrix(); 

	worldtransform_.translation_ = Add(worldtransform_.translation_, enemybulltvelocity_);

	
	if(--deathTimer_ <= 0) 
	{
	     isDead_ = true;
	}
	

}

void EnemyBullet::Draw(const ViewProjection& enemyviewprojection)
{


	model_->Draw(worldtransform_, enemyviewprojection, enemybullettextureHandle_);


}