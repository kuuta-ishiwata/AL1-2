#include "Ground.h"
#include <ImGuiManager.h>
#include <skydome.h>
#include "MATHEX.h"

void Ground::Initialize(Model* model)
{

	assert(model);

	model_ = model;

	worldtransform_.Initialize();

	worldtransform_.scale_ = {

	    0.5f,
	    0.5f,
	    0.5f,

	};


}

void Ground::Update()
{

	worldtransform_.UpdateMatrix();

}

void Ground::Draw(ViewProjection& viewProjection) {


	model_->Draw(worldtransform_, viewProjection);

}

