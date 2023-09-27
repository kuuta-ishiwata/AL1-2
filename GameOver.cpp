#include "DirectXCommon.h"
#include "GameScene.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Title.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "GameOver.h"

GameOver::GameOver() {}


GameOver::~GameOver() {

		delete GameoverSprite_;
}

void GameOver::Initialize() {

	dxCommom_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();

	

	end = TextureManager::Load("gameover.png");

	

	GameoverSprite_ = Sprite::Create(end, {0, 0});

}

void GameOver::Update() {

	

	if (input_->PushKey(DIK_SPACE)) 
	{

		isSceneEndGameOver =  true;
		isSceneEndGamePlay = false;

	}

}

void GameOver::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommom_->GetCommandList();

	Sprite::PreDraw(commandList);

	GameoverSprite_->Draw();
	
	Sprite::PostDraw();

	dxCommom_->ClearDepthBuffer();
}