#include "MATHEX.h"
#include <ImGuiManager.h>
#include <assert.h>
#include "RailCamera.h"
 

void RailCamera::Initialize(Vector3 position, Vector3 radian)
{

	//assert(model);

    model = model;

	worldtransform_.Initialize();
	
	//ワ－ルドトランスフォームの初期設定
	

	worldtransform_.rotation_.x;
	worldtransform_.rotation_.y;
	worldtransform_.rotation_.z;
	worldtransform_.translation_.x;
	worldtransform_.translation_.y;
	worldtransform_.translation_.z= -50;
	
	
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	//ビュープロジェクションの初期化
	viewprojection_.Initialize();

	viewprojection_.farZ = 800.0f;

}


void RailCamera::Update() 
{

	
	//worldtransform_.translation_ = Add(worldtransform_.translation_,worldtransform_.rotation_);

	//worldtransform_.TransferMatrix();

	viewprojection_.matView = Inverse(worldtransform_.matWorld_);

	//worldtransform_.translation_.z += 0.05f;
	
	worldtransform_.UpdateMatrix();
	

	ImGui::Begin("RailCamera");
	ImGui::SliderFloat3("translate", &worldtransform_.translation_.x, -50, 50.0f);
	ImGui::SliderFloat3("rotate", &worldtransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();
	

}