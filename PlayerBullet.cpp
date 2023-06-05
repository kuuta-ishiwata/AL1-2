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
	bullettextureHandle_ = TextureManager::Load("tex1.png");

	//引数で受取った初期座標をセット
	worldtransform_.Initialize();
	worldtransform_.translation_ = position;

	velocity_ = velocity;

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

void PlayerBullet::Draw(const ViewProjection& viewprojection) 
{

	model_->Draw(worldtransform_, viewprojection, bullettextureHandle_);

}


