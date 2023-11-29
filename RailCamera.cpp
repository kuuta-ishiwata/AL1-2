#include "RailCamera.h"
#include <ImGuiManager.h>
#include <assert.h>
#include "MATHEX.h"
    
void RailCamera::Initialize() 
{

	// assert(model);
	// 初期設定
	worldtransform_.translation_.z = -10;
	// ワールドトランスフォームの初期化
	worldtransform_.Initialize();

	// ビュープロジェクションの初期化
	// Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	viewprojection_.Initialize();
	viewprojection_.farZ = 3000.0f;
	

}



void RailCamera::Update()
{


	worldtransform_.UpdateMatrix();


	viewprojection_.matView = Inverse(worldtransform_.matWorld_);

	
	viewprojection_.UpdateMatrix();

}