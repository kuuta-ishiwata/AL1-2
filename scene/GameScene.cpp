#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() 
{


}

GameScene::~GameScene() 
{
	delete sprite_;
	delete model_;
	delete debugcamera_;
}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("debugfont.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
	worldtransform_.Initialize();
	viewprojection_.Initialize();
	//サウンドデータ読み込み
	soundDateHandle_ = audio_->LoadWave("fanfare.wav");
	audio_->PlayWave(soundDateHandle_);
	voichandle_ = audio_->PlayWave(soundDateHandle_, true);
	//ライン描画が参照するビュープロジェクションを指定する（アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewprojection_);
	//デバックカメラの生成
	debugcamera_ = new DebugCamera(20, 20);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugcamera_->GetViewProjection());
}

void GameScene::Update() { Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);
	ImGui::Begin("Debug1");
	//float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputfloat3);
	//デバックテキストの表示
	ImGui::Text("kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::SliderFloat3("Sliderfloat3", inputfloat3, 0.0f, 1.0f);
	ImGui::End();
	//デモウィンドウの表示を有効化
	ImGui::ShowDemoWindow();
	//スペースキー押した瞬間
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voichandle_);
	}
	//デバッグカメラ更新
	debugcamera_->Update();
}

void GameScene::Draw() {

	//ラインを描画する
	PrimitiveDrawer::GetInstance()->DrawLine3d({10, 0, 0}, {1, 0, 0}, {1,1,0,1.0});

	
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

	// モデルを連動する
	model_->Draw(worldtransform_, debugcamera_->GetViewProjection(), textureHandle_);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldtransform_, viewprojection_, textureHandle_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
