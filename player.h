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
	void Initiakize(Model* model, uint32_t textureHandle);
	//<summary>
	// 更新
	//<summary>
	void update();

	//<summary>
	// 描画
	////<summary>
	void Draw(ViewProjection& viewprojection);

private:
	// ワ－ルド変更データ
	WorldTransform worldtransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
