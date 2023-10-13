#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "player.h"
#include "PlayerBullet.h"
#include "Skydome.h"

GameScene::GameScene() 
{
	
	

}


GameScene::~GameScene() 
{

	
}


void GameScene::Initialize() {


	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("ga.png");

	skydomemodel_.reset(Model::CreateFromOBJ("skydome",true));


	worldtransform_.Initialize();
	viewProjection_.Initialize();
	
	model_.reset(Model::Create());
	
	// 自キャラの編成
	
	player_ = std::make_unique <Player>();
	

	//skydomemodel_ = std::make_unique<Model>();
	
	skydome_ = std::make_unique<Skydome>();

	// 自キャラの初期化
	player_->Initialize(model_.get(), textureHandle_);


	skydome_->Initialize(skydomemodel_.get());


	//viewProjection_.farZ = 1000.0f;


	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);


}

void GameScene::Update() { 

	skydome_->Update();
	// 自キャラの更新
	player_->Update();

	

	/*
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	*/

	
	
#ifdef  _DEBUG

	if (input_->TriggerKey(DIK_M))
	{
		isDebugCameraActive_ = true;
    }

#endif //  


	if (isDebugCameraActive_) 
	{
		debugCamera_->Update();	
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	
	} else {
	
	//ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

}

void GameScene::Draw() {
	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	
	
	skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理

	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();
	// スプライト描画後処理
	 Sprite::PostDraw();

#pragma endregion
}
