#pragma once

#include "WorldTransform.h"
#include "Model.h"

class Player{
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize(Model* model_, uint32_t textureHandle_);

	//更新
	void Update();

	//描画
	void Draw();

private:
	//ワールド変換行列
	WorldTransform worldTransform_;
	//モデル生成
	Model* model_ = new Model;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};

