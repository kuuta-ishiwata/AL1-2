#include "Player.h"
#include <assert.h>
#include <ImGuiManager.h>

void Player::Initialize(Model* model, uint32_t textureHandle)
{ 
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldtransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	// x,y,z方向のスケーリングを設定
	worldtransform_.scale_ = {2.0f, 1.0f, 1.0f};

	worldtransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldtransform_.Initialize();
	input_ = Input::GetInstance();

	
}



// 加算
Vector3 Add(const Vector3 v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
};


Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return result;
}


Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 1.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][0] = scale.x;
	result.m[3][1] = rot.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;

}


void Player::Update() {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	// 押した方向で移動ベクトルを変更

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}

	else if (input_->PushKey(DIK_RIGHT))
	{
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP))
	{
		move.y += kCharacterSpeed;
	}

	else if (input_->PushKey(DIK_DOWN))
	{
		move.y -= kCharacterSpeed;
	}

	worldtransform_.translation_= Add(worldtransform_.translation_, move);
	worldtransform_.matWorld_ = MakeAffineMatrix(
	    worldtransform_.scale_, worldtransform_.rotation_, worldtransform_.translation_);
	
	//スケーリング行列を宣言
	Matrix4x4 matScale = {0};
		matScale.m[0][0] = worldtransform_.scale_.x;
		matScale.m[1][1] = worldtransform_.scale_.y;
		matScale.m[2][2] = worldtransform_.scale_.z;
		matScale.m[3][3] = 1.0f;

	    Matrix4x4 matRotX = {0};
		matRotX.m[0][0] = 1.0f;
		matRotX.m[1][1] = cosf(worldtransform_.rotation_.x);
		matRotX.m[2][1] = -sinf(worldtransform_.rotation_.x);
		matRotX.m[1][2] = sinf(worldtransform_.rotation_.x);
		matRotX.m[2][2] = cosf(worldtransform_.rotation_.x);
		matRotX.m[3][3] = 1.0f;
		

	    Matrix4x4 matRotY = {0};
		matRotY.m[0][0] = cosf(worldtransform_.rotation_.y);
		matRotY.m[1][1] = 1.0f;
		matRotY.m[0][2] = -sinf(worldtransform_.rotation_.y);
		matRotY.m[2][0] = sinf(worldtransform_.rotation_.y);
		matRotY.m[2][2] = cosf(worldtransform_.rotation_.y);
		matRotY.m[3][3] = 1.0f;
		

	    Matrix4x4 matRotZ = {0};
		matRotZ.m[0][0] = cosf(worldtransform_.rotation_.z);
		matRotZ.m[1][0] = sinf(worldtransform_.rotation_.z);
		matRotZ.m[0][1] = -sinf(worldtransform_.rotation_.z);
		matRotZ.m[1][1] = cosf(worldtransform_.rotation_.z);
		matRotZ.m[2][2] = 1.0f;
		matRotZ.m[3][3] = 1.0f;


        //平行移動行列を宣言
	    Matrix4x4 matTrans = {0};

	    matTrans.m[0][0] = 1.0f;
	    matTrans.m[1][1] = 1.0f;
	    matTrans.m[2][2] = 1.0f;
	    matTrans.m[3][3] = 1.0f;
	    matTrans.m[3][0] = worldtransform_.translation_.x;
	    matTrans.m[3][1] = worldtransform_.translation_.y;
	    matTrans.m[3][2] = worldtransform_.translation_.z;


		/*
		worldtransform_.matWorld_ = MakeAffineMatrix(
	    worldtransform_.scale_, worldtransform_.rotation_, worldtransform_.translation_);
	   */
		//スケーリング行列
	Matrix4x4 matRot = Multiply(Multiply(matRotZ, matRotX), matRotY);

	//平行移動行列
	 worldtransform_.matWorld_ = Multiply(Multiply(matScale , matRot), matTrans);

	 worldtransform_.TransferMatrix();
	 
	 ImGui::Begin("Debug");
	 float playerPos[] = {
	     worldtransform_.translation_.x, worldtransform_.translation_.y,
	     worldtransform_.translation_.z};
	
	 ImGui::SliderFloat3("PlayerPos", playerPos, 1280, 720);

	 worldtransform_.translation_.x = playerPos[0];
	 worldtransform_.translation_.y = playerPos[1];
	 worldtransform_.translation_.z = playerPos[2];
	 ImGui::End();
	 
	 //移動限界座標
	 const float kMoveLimitX = 30.0f;
	 const float kMoveLimitY = 18.0f;

	 worldtransform_.translation_.x = max(worldtransform_.translation_.x, -kMoveLimitX);
	 worldtransform_.translation_.x = min(worldtransform_.translation_.x, +kMoveLimitX);
	 worldtransform_.translation_.y = max(worldtransform_.translation_.y, -kMoveLimitY);
	 worldtransform_.translation_.y = min(worldtransform_.translation_.y, +kMoveLimitY);

	 //デバックカメラ
	 


}


void Player::Draw(ViewProjection& viewprojection) {

	 model_->Draw(worldtransform_, viewprojection, textureHandle_);

}