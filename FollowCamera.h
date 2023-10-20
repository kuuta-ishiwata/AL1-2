#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class FollowCamera {

public:
	
 void Initialize();


 void Update();


 void SetTarget(const WorldTransform* target) { target_ = target; }

 private:

    ViewProjection* viewprojection_;	  

	Model* model_;
	WorldTransform* worldtransform_;

	const WorldTransform* target_ = nullptr;

	FollowCamera* followcamera_ = nullptr;


};
