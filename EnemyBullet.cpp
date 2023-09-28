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

Vector3 EnemyBullet::GetWorldPosition() {

	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)

	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
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

void EnemyBullet::OnCollision()
{

	isDead_ = true;


;}

void EnemyBullet::Draw(const ViewProjection& enemyviewprojection)
{

	
		 model_->Draw(worldtransform_, enemyviewprojection, enemybullettextureHandle_);


}