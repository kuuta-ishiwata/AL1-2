#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
#include <Input.h>

class Enemy
{
public:

	//<summary>
	//初期化
	//<summary>

	void Initialize(Model* model, uint32_t enemytextureHandle);


	///<summary>
	/// 更新
	///<summary>
	void Update();

    ///<symmary>
	///描画
	/// <summary>
	void Draw(ViewProjection& enemyviewprojection);

private:

	WorldTransform worldtransform_;
	ViewProjection enemyviewprojection_;

	Model* model_ = nullptr;

	uint32_t enemytextureHandle_ = 0u;

	Input* input_ = nullptr;




};
