#pragma once
#include "Model.h"
#include "PrimitiveDrawer.h"
#include "WorldTransform.h"
#include <assert.h>
class player {

public:
	//<summary>
	// ������
	//<summary>
	void Initiakize(Model* model,uint32_t textureHandle)
	{
		//��������󂯎�������f�����ǂݍ��܂ꂢ�邩�`�F�N
		assert(model);
		//�������烂�f���ƃe�N�X�`���n���h�����󂯎��
		model_  = model;
		textureHandle_ = textureHandle;
		//���|���h�g�����X�t�H�|��������
		worldtransform_.Initialize();
	}
	//<summary>
	// �X�V
	//<summary>
	void update() {

	}
	//<summary>
	// �`��
	////<summary>
	void Draw();

private:
	// ���|���h�ύX�f�[�^
	WorldTransform worldtransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = ;
};
