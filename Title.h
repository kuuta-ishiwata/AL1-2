#pragma once
#include"Audio.h"
#include"DirectXCommon.h"
#include"Input.h"
#include"Model.h"
#include"SafeDelete.h"
#include"Sprite.h"
#include"ViewProjection.h"
#include"WorldTransform.h"
#include "Scene.h"


class Title {
public:
	
	///<summary>
	///コンストラクタ
	///<summary>
	Title();


	///< summary>
	/// デストラクタ
	///< summary>
	~Title();


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
	
	void Draw();

    



	bool IsSceneEnd() { return isSceneEnd; }

	SceneType NextScenekTitle() { return SceneType::kTitle; }


private: //メンバ変数


	DirectXCommon* dxCommom_ = nullptr;


	Input* input_ = nullptr;
	Audio* audio_ = nullptr;


	bool isSceneEnd = false;
	//bool isSceneEndGamePlay = false;
	

	Title* titleScene = nullptr;
	Title* sceneNo = nullptr;

	
	bool isDead = false;

	ViewProjection viewProjection_;

	uint32_t Start = 0;
	uint32_t end = 0;


	Sprite* Sprite_ = nullptr;
	Sprite* GameoverSprite_ = nullptr;

};

