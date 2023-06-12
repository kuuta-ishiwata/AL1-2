#include <assert.h>
#include <ImGuiManager.h>
#include "Enemy.h"
#include "MATHEX.h"
#include<assert.h>

void Enemy::Initialize(Model* model, uint32_t enemytextureHandle)
{ 


	assert(model);
	model_ = model;

	enemytextureHandle_ = enemytextureHandle;
	worldtransform_.Initialize();
	
	worldtransform_.translation_ = {0.0f, 2.0f, 0.0f};
	
	
	

}

void Enemy::Update() 
{

	Vector3 move = {0, 0, 0};

	const float kenemyspeed = 0.2f;

	 move.z -= kenemyspeed; 
     worldtransform_.translation_.z -= kenemyspeed;
	worldtransform_.UpdateMatrix();


}

void Enemy::Draw(ViewProjection& enemyviewprojection)
{

	model_->Draw(worldtransform_, enemyviewprojection, enemytextureHandle_);


}