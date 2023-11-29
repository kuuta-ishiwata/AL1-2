#include "Player.h"
#include <assert.h>
#include <ImGuiManager.h>
#include "PlayerBullet.h"
#include "MATHEX.h"


//Player::Player() {}
//Player::~Player() {}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}


void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm_, Model* modelR_arm) { 

	//assert(model);
	//model_ = model;
	modelFighterBody_ = modelBody;
	modelFighterhead_ = modelHead;
	modelFighterL_arm_ = modelL_arm_;
	modelFighterR_arm_ = modelR_arm;
	//textureHandle_ = textureHandle;

	// x,y,z方向のスケーリングを設定
	worldtransform_.scale_ = {2.0f, 2.0f, 2.0f};

	worldtransform_.translation_ = {0.0f, 2.0f, 0.0f};



	worldtransform_.Initialize();
	input_ = Input::GetInstance();

	//bulletの解放
	//for (PlayerBullet* bullet : bullets_)
	//{
	//	delete bullet;
	//}

}




void Player::InitializeFloatingGimmick() 
{ 

   floatingParameter_ = 0.0f;

}

void Player::UpdateFloatingGimmick() 
{

  const uint16_t Cycle = 120;

  const float Step = 2.0f * (float)M_PI / Cycle;

  floatingParameter_ += Step;

  floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);

  const float Floatingamplitude = 0.5f;

  //浮遊を座標に反映
  WorldTransformBody.translation_.y = std::sin(floatingParameter_) * Floatingamplitude;

   
  
}


void Player::Update() {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	// 押した方向で移動ベクトルを変更

	if (input_->PushKey(DIK_LEFT)) 
	{
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

	
	// 回転速さ[ラジアン/frane]
	const float kRotspeed = 0.02f;

	// 押した方向で移動ベクトルを変更

	if (input_->PushKey(DIK_A)) {
		worldtransform_.rotation_.y -= kRotspeed;
	}
	if (input_->PushKey(DIK_D)) {
		worldtransform_.rotation_.y += kRotspeed;
	}

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{

		//速さ
		const float speed = 0.3f;

		//移動量
    	 move =
		{
			(float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed,
			 0.0f,
			(float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed 
		};


	     Normalize(move);
		 Multiply2(speed,move);
	     
		worldtransform_.translation_ = Add(worldtransform_.translation_, move);

	}
	
	worldtransform_.UpdateMatrix();
	 
	 //移動限界座標
	 const float kMoveLimitX = 30.0f;
	 const float kMoveLimitY = 18.0f;

	 worldtransform_.translation_.x = max(worldtransform_.translation_.x, -kMoveLimitX);
	 worldtransform_.translation_.x = min(worldtransform_.translation_.x, +kMoveLimitX);
	 worldtransform_.translation_.y = max(worldtransform_.translation_.y, -kMoveLimitY);
	 worldtransform_.translation_.y = min(worldtransform_.translation_.y, +kMoveLimitY);
	 worldtransform_.translation_ = Add(worldtransform_.translation_, move);
	 
	 /*
	 worldtransform_.matWorld_ = MakeAffineMatrix(
	     worldtransform_.scale_, worldtransform_.rotation_, worldtransform_.translation_);

	 worldtransform_.TransferMatrix();
	 */
	 worldtransform_.UpdateMatrix();


	 

	 //キャラクター攻撃
	 
	//
	//  Attack(worldtransform_.translation_);

	 //弾更新
	 /*
	 if (bullet_) 
	 {
		bullet_->Update();
	 }
	 */
	 /*
	 for (PlayerBullet* bullet : bullets_ ) 
	 {
		bullet->Update();
	 }
	 */
	 //ワールドトランスフォームの更新
	




	 /* ImGui::Begin("Debug");
	 float playerPos[] = {
	     worldtransform_.translation_.x, worldtransform_.translation_.y,
	     worldtransform_.translation_.z};

	 ImGui::SliderFloat3("PlayerPos", playerPos, 1280, 720);

	 worldtransform_.translation_.x = playerPos[0];
	 worldtransform_.translation_.y = playerPos[1];
	 worldtransform_.translation_.z = playerPos[2];
	 ImGui::End();
	 */

}


void Player::Draw(ViewProjection& viewprojection) 
{

	modelFighterBody_->Draw(WorldTransformBody, viewprojection );
	modelFighterhead_->Draw(WorldTransformHead, viewprojection);
	modelFighterL_arm_->Draw(WorldTransformL_arm, viewprojection);
	modelFighterR_arm_->Draw(WorldTransformR_arm, viewprojection);

	 // 弾描画
	 //for (PlayerBullet* bullet : bullets_)
	 //{
	//	bullet->Draw(viewprojection);
	 //}
	 
}






