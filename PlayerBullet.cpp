#include "PlayerBullet.h"
#include <assert.h>
#include "WorldTransform.h"
#include <ImGuiManager.h>
#include "MATHEX.h"


void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3 velocity)
{ 
	
	assert(model);
	model_ = model;
	//テクスチャ読み
	bullettextureHandle_ = TextureManager::Load("uvChecker.png");

	//引数で受取った初期座標をセット
	worldtransform_.Initialize();
	worldtransform_.translation_ = position;

	velocity_ = velocity;

}


Vector3 PlayerBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}



void PlayerBullet::Update()
{ 
	
	worldtransform_.UpdateMatrix();

	worldtransform_.translation_=  Add(worldtransform_.translation_,velocity_);

	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}

}

void PlayerBullet::OnCollision() 
{ 

	isDead_ = true;

}

void PlayerBullet::Draw(const ViewProjection& viewprojection) 
{

	model_->Draw(worldtransform_, viewprojection, bullettextureHandle_);

}


