#include "player.h"
#include "cassert.h"


void Player::Initialize(Model* model, uint32_t textureHandle)
{ 
	
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle; 

	worldTransform_.Initialize();
}

