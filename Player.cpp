#include "Player.h"
#include <assert.h>
#include <ImGuiManager.h>
#include "PlayerBullet.h"
#include "MATHEX.h"




void Player::Initialize(Model* model, uint32_t textureHandle)
{ 

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldtransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	// x,y,z方向のスケーリングを設定
	worldtransform_.scale_ = {2.0f, 2.0f, 2.0f};

	worldtransform_.translation_ = {50.0f, 1.0f, 0.0f};

	worldtransform_.Initialize();
	input_ = Input::GetInstance();

	//bulletの解放
	for (PlayerBullet* bullet : bullets_)
	{

		delete bullet;
	}


}


Vector3 Player::GetWorldPosition() 
{ 
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Attack(Vector3& position)
{
	if (input_->PushKey(DIK_SPACE))
	{   
		
		//弾があれば解放
		/*
		if (bullet_)
		{
			delete bullet_;
			bullet_ = nullptr;
		}
		*/
		
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//速度ベクトルを自機の向きに合わせて回転
		velocity = TransformNomal(velocity,worldtransform_.matWorld_);

		// 弾を生成し初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_,position,velocity);

		// 弾を登録
		//bullet_ = newBullet;
		bullets_.push_back(newBullet);

	}

}

void Player::OnCollision()
{

}

void Player::Update()
{

	//デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
		   
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
	 
	 Attack(worldtransform_.translation_);

	 //弾更新
	 /*
	 if (bullet_) 
	 {
		bullet_->Update();
	 }
	 */

	 for (PlayerBullet* bullet : bullets_ ) 
	 {
		bullet->Update();
	 }
	 
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




void Player::Draw(ViewProjection& viewprojection) {

	 model_->Draw(worldtransform_, viewprojection, textureHandle_);

	 // 弾描画
	 for (PlayerBullet* bullet : bullets_)
	 {

		 bullet->Draw(viewprojection);

	 }
	 
}



 





