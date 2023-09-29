#include "Player.h"
#include <assert.h>
#include <ImGuiManager.h>
#include "PlayerBullet.h"
#include "MATHEX.h"


Player::~Player() 
{ 

	
	// bulletの解放
	for (PlayerBullet* bullet : bullets_) 
	{

		delete bullet;

	}
	delete sprite2DReticle_;

}

void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 Position) {
	
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldtransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	// x,y,z方向のスケーリングを設定
	worldtransform_.Initialize();
	worldtransform_.scale_ = {2.0f, 2.0f, 2.0f};

	worldtransform_.translation_ = Position;


	worldtransform_.UpdateMatrix();
	input_ = Input::GetInstance();



	worldTransform3DReticle_.Initialize();
	
	
	//レティクル用テクスチャ
	uint32_t textureReticle = TextureManager::Load("aim.png");

	//スプライト生成
	sprite2DReticle_ = Sprite::Create(textureReticle,ReticlePos_, color_,anchor_);


}





void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{   
		
		//弾の速度
		const float kBulletSpeed = 0.2f;
		Vector3 velocity(0, 0, kBulletSpeed);           



		//速度ベクトルを自機の向きに合わせて回転
		// velocity = TransformNomal(velocity,worldtransform_.matWorld_);

		velocity.x = worldTransform3DReticle_.translation_.x - worldtransform_.translation_.x;
		velocity.y = worldTransform3DReticle_.translation_.y - worldtransform_.translation_.y;
		velocity.z = worldTransform3DReticle_.translation_.z - worldtransform_.translation_.z;

		velocity =  Normalize(velocity);

		// 弾を生成し初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録
		bullets_.push_back(newBullet);
	}

}

void Player::OnCollision() 
{ 


    isDead_ = true;

}

void Player::Restart()
{ 
	
	isDead_ = false;
	


}


void Player::Update(ViewProjection viewprojection) {



	//デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
    


	Vector3 move = {0, 0, 0};

	
	const float kCharacterSpeed = 0.1f;
	
	// 押した方向で移動ベクトルを変更

	if (input_->PushKey(DIK_A)) 
	{
		move.x -= kCharacterSpeed;
	}

	else if (input_->PushKey(DIK_D))
	{
		move.x += kCharacterSpeed;
	}


	if (input_->PushKey(DIK_W))
	{
		move.y += kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_S))
	{
		move.y -= kCharacterSpeed;
	}

	
	// 回転速さ[ラジアン/frane]
	const float kRotspeed = 0.02f;

	// 押した方向で移動ベクトルを変更

	if (input_->PushKey(DIK_LEFT)) {
		worldtransform_.rotation_.y -= kRotspeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		worldtransform_.rotation_.y += kRotspeed;
	}

	
	 // キャラクター攻撃

	Attack();

	for (PlayerBullet* bullet : bullets_) {

		bullet->Update();
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
		 */
	 //worldtransform_.TransferMatrix();
	 
	 worldtransform_.UpdateMatrix();
	 

	
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



		 //マウスカーソル
		 POINT mousePosition;
	     // マウス座標（スクリーン座標）を取得
	     GetCursorPos(&mousePosition);

	    // クライアントエリア座標に変換する
	     HWND hwnd = WinApp::GetInstance()->GetHwnd();
	     ScreenToClient(hwnd, &mousePosition);

	     // マウス座標を2Dレティクルのスプライトに代入する
	      ReticlePos_.x = (float)mousePosition.x;
	      ReticlePos_.y = (float)mousePosition.y;

	     sprite2DReticle_->SetPosition(ReticlePos_);


	    Matrix4x4 matViewport =
	         MakeViewPortMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	    // ビュープロジェクションビューポート合成行列
	     Matrix4x4 matVPV = Multiply(viewprojection.matView, Multiply(viewprojection.matProjection, matViewport));
	     // 合成行列の逆行列を計算する
	     Matrix4x4 matInversVPV = Inverse(matVPV);


		 //スクリーン座標

	     Vector3 posNear =
	         Vector3((float)sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y, 0);

	     Vector3 posFar =
	         Vector3((float)sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y, 1);


		 //スクリーン座標系からワールド座標系へ
	     posNear = Transform(posNear, matInversVPV);
	     posFar = Transform(posFar, matInversVPV);


		 //マウスレイの方向
	     Vector3 mouseDirection = Substract(posFar, posNear);
	     mouseDirection = Normalize(mouseDirection);


		 //カメラから照準のオブジェクト
	     const float kDistanceTestObject = 80.0f;

		 worldTransform3DReticle_.translation_.x = posNear.x + mouseDirection.x * kDistanceTestObject;
	     worldTransform3DReticle_.translation_.y = posNear.y + mouseDirection.y * kDistanceTestObject;
	     worldTransform3DReticle_.translation_.z = posNear.z + mouseDirection.z * kDistanceTestObject;

		 
		 //worldTransform3DReticleのワールド行列更新と転送
	     worldTransform3DReticle_.UpdateMatrix();
		


}




Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldtransform_.matWorld_.m[3][0];
	worldPos.y = worldtransform_.matWorld_.m[3][1];
	worldPos.z = worldtransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::SetParent(const WorldTransform* parent)
{ 

	worldtransform_.parent_ = parent; 

}



void Player::Draw(ViewProjection& viewprojection) 
{
	

	 
		   model_->Draw(worldtransform_, viewprojection, textureHandle_);


	 

	 
	
	 // 弾描画
	 for (PlayerBullet* bullet : bullets_)
	 {

		 bullet->Draw(viewprojection);

	 }
	 
	 

//	 model_->Draw(worldTransform3DReticle_, viewprojection);

	 

}


void Player::DrawUI() { sprite2DReticle_->Draw(); }
 





