
#include "FollowCamera.h"
#include "MATHEX.h"

void FollowCamera::Initialize()
{
	
	viewprojection_.Initialize();
	worldtransform_.Initialize();
	
}

void FollowCamera::Update() 
{


	
	if (target_)
	{
		//追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};
			
		//座標をコピーしてオフセット分ずらす
		viewprojection_.translation_ = Add(target_->translation_, offset);


	}

	viewprojection_.UpdateMatrix();



}
