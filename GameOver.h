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

    class GameOver {
public:
	///< summary>
	/// �R���X�g���N�^
	///< summary>
	GameOver();

	///< summary>
	/// �f�X�g���N�^
	///< summary>
	~GameOver();

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

	
	bool IsSceneEndGameover() { return isSceneEndGameOver; }
	bool IsSceneEndGamePlay() { return isSceneEndGamePlay; }
	SceneType NextSceneGameOver() { return SceneType::gameover; }
	

private: // �����o�ϐ�

	DirectXCommon* dxCommom_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	
	bool isSceneEndGameOver = false;
	bool isSceneEndGamePlay = false;

	GameOver* titleScene = nullptr;
	GameOver* sceneNo = nullptr;

	bool isDead = false;

	ViewProjection viewProjection_;

	uint32_t end = 0;


	Sprite* GameoverSprite_ = nullptr;


};