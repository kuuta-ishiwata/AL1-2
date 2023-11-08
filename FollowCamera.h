#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MATHEX.h"
#include "PrimitiveDrawer.h"
#include "DebugCamera.h"


class FollowCamera {

public:
	
  void Initialize();
	

 

  void Update();




  void SetTarget(const WorldTransform* target) { target_ = target; }
  const ViewProjection& GetviewProjection() { return viewprojection_; }

 private:

    
	Model* model_;
	WorldTransform worldtransform_;
	ViewProjection viewprojection_;	  


	const WorldTransform* target_ = nullptr;

	FollowCamera* followcamera_ = nullptr;


};
