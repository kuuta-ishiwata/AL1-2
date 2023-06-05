#include "PlayerBullet.h"
#include <assert.h>
#include "WorldTransform.h"
#include <ImGuiManager.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{ 
	
	assert(model);

	model_ = model;
	//テクスチャ読み
	bullettextureHandle_ = TextureManager::Load("tex1.png");

	//引数で受取った初期座標をセット
	worldtransform_.Initialize();
	worldtransform_.translation_ = position;


}

void PlayerBullet::Update()
{ 
	
	worldtransform_.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewprojection) 
{

	model_->Draw(worldtransform_, viewprojection, bullettextureHandle_);

}


