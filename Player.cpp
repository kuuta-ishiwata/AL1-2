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
	worldtransform_.scale_ = {2.0f, 2.0f, 2.0f};

	worldtransform_.translation_ = {50.0f, 1.0f, 0.0f};

	worldtransform_.Initialize();
	input_ = Input::GetInstance();

	

	worldTransform3DReticle_.Initialize();
	
	
	//レティクル用テクスチャ
	uint32_t textureReticle = TextureManager::Load("aim.png");

	//スプライト生成
	sprite2DReticle_ = Sprite::Create(textureReticle,ReticlePos_, color_,anchor_);
;    

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



		velocity.x = worldTransform3DReticle_.translation_.x - worldtransform_.translation_.x;
		velocity.y = worldTransform3DReticle_.translation_.y - worldtransform_.translation_.y;
		velocity.z = worldTransform3DReticle_.translation_.z - worldtransform_.translation_.z;

		 velocity =  Normalize(velocity);

		 velocity.x * kBulletSpeed;
		 velocity.y * kBulletSpeed;
		 velocity.z * kBulletSpeed;

	}

	
}

void Player::OnCollision()
{ isDead_ = true; }


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
		 */
	 //worldtransform_.TransferMatrix();
	 
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

	  //自機のワールド座標ら3Dレティクールのワールド座標を計算

	  //自機から3Dレティクル
	 
		const float kDistancePlayerTo3DReticle = 50.0f;

		// 時機から3Dレティクルへのオフセット（Z向き）
		Vector3 offeset = {0, 0, 1.0f};

		// 自機にワールド行列の回転を反映
		offeset = TransformNomal(offeset, worldtransform_.matWorld_);

		// ベクトルの長さを整える
		offeset = Normalize(offeset);

		offeset.x *= kDistancePlayerTo3DReticle;
		offeset.y *= kDistancePlayerTo3DReticle;
		offeset.z *= kDistancePlayerTo3DReticle;

		// 3Dレティクルの座標を設定

		worldTransform3DReticle_.translation_.x = offeset.x + GetWorldPosition().x;
		worldTransform3DReticle_.translation_.y = offeset.y + GetWorldPosition().y;
		worldTransform3DReticle_.translation_.z = offeset.z + GetWorldPosition().z;


		// worldTransform3DReticle_のワールド行列更新と転送
		worldTransform3DReticle_.UpdateMatrix();
	    
		//UpdateUI(viewProjection_);
		
		//POINT mousePosition;
		//マウス座標（スクリーン座標）を取得
	    //GetCursorPos(&mousePosition);
		

		//クライアントエリア座標に変換する
		//HWND hwnd = WinApp::GetInstance()->GetHwnd();
		//ScreenToClient(hwnd, &mousePosition);

		//マウス座標を2Dレティクルのスプライトに代入する
		//mousePosition = 

		//ビュープロジェクションビューポート合成行列
		//Matrix4x4 matVDV = 
		//合成行列の逆行列を計算する

		

		Vector3 positionReticle = worldTransform3DReticle_.translation_;

	    Matrix4x4 matViewport =
	        MakeViewPortMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	    Matrix4x4 matViewprojectionviewport =
	        Multiply(viewprojection.matView, Multiply(viewprojection.matProjection, matViewport));

	    positionReticle = Transform(positionReticle, matViewprojectionviewport);

	    sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
}

/*
void Player::UpdateUI(ViewProjection viewProjection)
 {

	/*
	Vector3 positionReticle = worldTransform3DReticle_.translation_;

	Matrix4x4 matViewport =
	    MakeViewPortMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	Matrix4x4 matViewprojectionviewport =
		Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));

	positionReticle = Transform(positionReticle, matViewprojectionviewport);

	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
	*/


//}


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

void Player::Draw(ViewProjection& viewprojection) {

	 model_->Draw(worldtransform_, viewprojection, textureHandle_);

	 // 弾描画
	 for (PlayerBullet* bullet : bullets_)
	 {
		 bullet->Draw(viewprojection);

	 }
	 
//	 model_->Draw(worldTransform3DReticle_, viewprojection);

	 

}

void Player::DrawUI() { sprite2DReticle_->Draw(); }
 





