#include "FollowCamera.h"

void FollowCamera::Initialize()
{
	
	viewprojection_->Initialize();
	worldtransform_->Initialize();
}

void FollowCamera::Update() 
{

	followcamera_->Update();


}
