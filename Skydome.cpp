#include "Skydome.h"
#include <ImGuiManager.h>
#include <skydome.h>
#include "MATHEX.h"

void Skydome::Initialize(Model* model) {

	assert(model);

	model_ = model;

	worldtransform_.Initialize();

	worldtransform_.scale_ = 
	{

	    80.0f,
	    80.0f,
	    80.0f,

	};
}

void Skydome::Update() { worldtransform_.UpdateMatrix(); }

void Skydome::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldtransform_, viewProjection);
}

