#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include<assert.h>
#include <Input.h>
#include "Model.h"
#include "PrimitiveDrawer.h"
class PlayerBullet
{
public: 
	///<summary>
	///初期化
	/// </summary>
	/// <param name= "model">モデル</param>
	/// <param name = "position">初期化座標</param>
	
	void Initialize(Model* model, const Vector3& position);
	

	///<summary>
	///更新
	/// </summary>
	void Update();


	///<summary>
	//描画
	///</summary>
	///<param name="viewProjection">ビュープロジェクション</param>
	
	void Draw(const ViewProjection& viewprojection);

	private:
		//ワールド変更データ
	WorldTransform worldtransform_;
	ViewProjection viewProjection_;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル

	uint32_t bullettextureHandle_ = 0u;
	Input* input_ = nullptr;
	
	
};
