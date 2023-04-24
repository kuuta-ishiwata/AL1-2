#include "Player.h"
#include <assert.h>

void player::Initiakize(Model* model, uint32_t textureHandle)
{ 
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle; 
	worldtransform_.Initialize();
}

void player::Draw(ViewProjection& viewprojection) {
	model_->Draw(worldtransform_, viewprojection, textureHandle_);
}

void player::update() {

}
