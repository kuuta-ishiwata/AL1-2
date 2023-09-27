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
	///�R���X�g���N�^
	///<summary>
	Title();


	///< summary>
	/// �f�X�g���N�^
	///< summary>
	~Title();


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

    



	bool IsSceneEnd() { return isSceneEnd; }

	SceneType NextScenekTitle() { return SceneType::kTitle; }


private: //�����o�ϐ�


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

