#include "Player.h"

//�R���X�g���N�^
Player::Player() {

}
//�f�X�g���N�^
Player::~Player() {
	delete model_;
}

//������
void Player::Initialize(Model* model_, uint32_t textureHandle_) {
	worldTransform_.Initialize();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
}

//�X�V
void Player::Update() {
	Vector3 move(0, 0, 0);

	
}

//�`��
void Player::Draw() {
	
}
