#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Skydome {


public:
	
	///<summary>
	///初期化
	/// <summary>

	void Initialize(Model* model);

	///< summary>
	/// 初期化
	///  <summary>
	void Update();

	///< summary>
	/// 描画
	///  <summary>
	void Draw(ViewProjection &viewprojection);


private:

	//ワールド変更データ
	WorldTransform worldtransform_;

	//モデル
	Model* model_ = nullptr;

	ViewProjection  viewprojection_;
	

};