#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class GameClear {
public:
	GameClear();


	~GameClear();

	///< summary>
	/// ������
	///< summary>
	void Initialize();

	//////<summary>
	/// ���t���[��
	///< summary>
	void Update();

	///< summary>
	/// �`��
	///< summary>

	void Draw();

	void Reset();

	bool IsSceneEnd() { return isSceneEnd; }

	SceneType NextScene() { return SceneType::kGameClear; }

private:

	DirectXCommon* dxCommom_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd = false;

	ViewProjection viewProjection_;

	uint32_t Clear = 0;

	Sprite* GameClearSprite_ = nullptr;


};

