#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
class player {

public:
	//<summary>
	// 初期化
	//<summary>
	void Initiakize(Model* model,uint32_t textureHandle)
	{
		//引数から受け取ったモデルが読み込まれいるかチェク
		assert(model);
		//引数からモデルとテクスチャハンドルを受け取る
		model_  = model;
		textureHandle_ = textureHandle;
		//ワ－ルドトランスフォ－ム初期化
		worldtransform_.Initialize();
	}
	//<summary>
	// 更新
	//<summary>
	void update() {

	}
	//<summary>
	// 描画
	////<summary>
	void Draw();

private:
	// ワ－ルド変更データ
	WorldTransform worldtransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = ;
};
