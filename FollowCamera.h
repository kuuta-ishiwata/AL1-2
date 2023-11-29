#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class FollowCamera {

public:
	
	void SetTarget(const WorldTransform* target) { target_ = target; }
	const ViewProjection& GetviewProjection() { return viewprojection_; }


  void Initialize();
	


  void Update();



 private:

    
	
	//WorldTransform worldtransform_;
	ViewProjection viewprojection_;	  


	const WorldTransform* target_ = nullptr;

	


};
