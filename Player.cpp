#include "Player.h"

//コンストラクタ
Player::Player() {

}
//デストラクタ
Player::~Player() {
	delete model_;
}

//初期化
void Player::Initialize(Model* model_, uint32_t textureHandle_) {
	worldTransform_.Initialize();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
}

//更新
void Player::Update() {
	Vector3 move(0, 0, 0);

	
}

//描画
void Player::Draw() {
	
}
