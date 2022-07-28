#pragma once

#include "WorldTransform.h"
#include "Model.h"

class Player{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//������
	void Initialize(Model* model_, uint32_t textureHandle_);

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	//���[���h�ϊ��s��
	WorldTransform worldTransform_;
	//���f������
	Model* model_ = new Model;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

};

