
#include "FollowCamera.h"
#include "MATHEX.h"
#include <Input.h>
#include <Xinput.h>

void FollowCamera::Initialize()
{
	
	viewprojection_.Initialize();
	viewprojection_.farZ = 1400.0f;
   
}

void FollowCamera::Update() 
{

	if (target_)
	{

		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -40.0f};
		// カメラの角度から回転行列を計算
		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_.rotation_);

		// オフセットをカメラの回転に合わせて回転
		offset = TransformNormal(offset, rotateMatrix);

		// 座標をコピーしてオフセットずらす
		viewprojection_.translation_ = Add(target_->translation_, offset);


	}

	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) 
	{

		const float kRadian = 0.01f;
		viewprojection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kRadian;
		viewprojection_.rotation_.x += (float)joyState.Gamepad.sThumbRY / SHRT_MAX * kRadian;


	}

	// ビュー行列の更新
	viewprojection_.UpdateMatrix();
	
}