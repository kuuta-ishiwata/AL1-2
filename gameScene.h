#pragma once
#include"Audio.h"
#include"DirectXCommon.h"
#include"Input.h"
#include"Model.h"
#include"SafeDelete.h"
#include"Sprite.h"
#include"ViewProjection.h"
#include"WorldTransform.h"



class gameScene {
public:
	
	///<summary>
	///コンストラクタ
	///<summary>
	gameScene();


	///< summary>
	/// デストラクタ
	///< summary>
	~gameScene();


	///< summary>
	/// 初期化
	///< summary>
	void Initialize();

	//////<summary>
	/// 毎フレーム
	///< summary>
	void Update();


	///< summary>
	/// 描画
	///< summary>
	gameScene();





private:
};

