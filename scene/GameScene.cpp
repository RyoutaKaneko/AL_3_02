#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <random>

GameScene::GameScene() {
	for (int i = 0; i < 100; i++) {
		p1[i] = { 50,-4,-50 + addNum };
		p2[i] = { -50,-4,-50 + addNum };
		p3[i] = { -50 + addNum,-4,50 };
		p4[i] = { -50 + addNum,-4,-50 };
		addNum++;
	}
	for (int i = 0; i < 2; i++) {
		v[i].x = 0;
		v[i].y = 0;
		v[i].z = 0;
		a[i].x = 0;
		a[i].y = 0;
		a[i].z = 0;
		force[i].x = 0;
		force[i].y = 0;
		force[i].z = 0;
	}
}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	/*debugCamera_ = new DebugCamera(1280, 720);*/

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("white1x1.png");
	mario = TextureManager::Load("purin.jpg");
	model_ = Model::Create();
	for (int i = 0; i < 2; i++) {
		worldTransform_[i].Initialize();
	}
	/*worldTransform_[1].translation_ = { 1,-1,1 };
	worldTransform_[1].parent_ = &worldTransform_[0];*/
	viewProjection_.Initialize();
	viewProjection_.eye = { -15,8,-15 };
	/*viewProjection_.fovAngleY = Radian(10.0f);*/
	viewProjection_.UpdateMatrix();
	//デバックカメラの生成
	/*debugCamera_ = new DebugCamera(1280, 720);*/
	////軸方向の表示を有効にする
	//AxisIndicator::GetInstance()->SetVisible(true);
	////軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//ライン描画
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::uniform_real_distribution<float> dist(-50, 50);

}

void GameScene::Update() {
	////yの仮ベクトル
	//Vector3 yTmpVec(0, 1, 0);
	//yTmpVec.normalize();
	//Vector3 downVec(0, -1, 0);
	//downVec.normalize();
	////正面仮ベクトル
	//Vector3 frontTmp = viewProjection_.target - viewProjection_.eye;
	//frontTmp.normalize();
	////右ベクトル
	//Vector3 rightVec = yTmpVec.cross(frontTmp);
	//rightVec.normalize();
	////左ベクトル
	//Vector3 leftVec = frontTmp.cross(yTmpVec);
	//leftVec.normalize();
	////正面ベクトル
	//Vector3 frontVec = rightVec.cross(yTmpVec);
	//frontVec.normalize();
	////背面ベクトル
	//Vector3 behindVec = frontVec * -1;

	//Vector3 move(0, 0, 0);

	//float kRotSpeed = 0.005f;
	/*float kSpeed = 1;*/

	if (input_->PushKey(DIK_W)) {
		point.y += 0.5f;
	}
	if (input_->PushKey(DIK_S)) {
		point.y -= 0.5f;
	}
	if (input_->PushKey(DIK_A)) {
		point.x -= 0.5f;
	}
	if (input_->PushKey(DIK_D)) {
		point.x += 0.5f;
	}
	if (input_->PushKey(DIK_R)) {
		point.z += 0.5f;
	}
	if (input_->PushKey(DIK_F)) {
		point.z -= 0.5f;
	}

	if (input_->PushKey(DIK_LEFT)) {
		point.x -= 3;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		point.x += 3;
	}

	// バネ

	//1個目
	//x
	force[0].x = (point.x - worldTransform_[0].translation_.x) * stiffness;
	a[0].x = force[0].x / mass;
	v[0].x = damping * (v[0].x + a[0].x);
	worldTransform_[0].translation_.x += v[0].x;
	//y
	force[0].y = (point.y - worldTransform_[0].translation_.y) * stiffness;
	force[0].y -= gravity[0];
	a[0].y = force[0].y / mass;
	v[0].y = damping * (v[0].y - a[0].y);
	worldTransform_[0].translation_.y -= v[0].y;
	//z
	force[0].z = (point.z - worldTransform_[0].translation_.z) * stiffness;
	a[0].z = force[0].z / mass;
	v[0].z = damping * (v[0].z + a[0].z);
	worldTransform_[0].translation_.z += v[0].z;

	////2個目////
	force[0].x = (point.x - worldTransform_[0].translation_.x) * stiffness;
	a[0].x = force[0].x / mass;
	v[0].x = damping * (v[0].x + a[0].x);
	worldTransform_[0].translation_.x += v[0].x;
	//y
	force[0].y = (point.y - worldTransform_[0].translation_.y) * stiffness;
	force[0].y -= gravity[0];
	a[0].y = force[0].y / mass;
	v[0].y = damping * (v[0].y - a[0].y);
	worldTransform_[0].translation_.y -= v[0].y;
	//z
	force[0].z = (point.z - worldTransform_[0].translation_.z) * stiffness;
	a[0].z = force[0].z / mass;
	v[0].z = damping * (v[0].z + a[0].z);
	worldTransform_[0].translation_.z += v[0].z;

	//switch (scene) {
	//case 0:
	//	//バイオ
	//	if (input_->TriggerKey(DIK_Q)) {
	//		scene = 1;
	//	}

	//	//移動
	//	if (input_->PushKey(DIK_W)) {
	//		move.x = sin(worldTransform_[0].rotation_.y);
	//		move.z = cos(worldTransform_[0].rotation_.y);
	//	}
	//	if (input_->PushKey(DIK_S)) {
	//		move.x = sin(worldTransform_[0].rotation_.y) * -1;
	//		move.z = cos(worldTransform_[0].rotation_.y) * -1;
	//	}

	//	worldTransform_[0].translation_ += move;

	//	//回転
	//	if (input_->PushKey(DIK_LEFT)) {
	//		worldTransform_[0].rotation_.y -= kRotSpeed;
	//	}
	//	if (input_->PushKey(DIK_RIGHT)) {
	//		worldTransform_[0].rotation_.y += kRotSpeed;
	//	}
	//	break;
	//case 1:
	//	//カメラ
	//	if (input_->TriggerKey(DIK_Q)) {
	//		scene = 2;
	//	}

	//	if (input_->PushKey(DIK_W)) {
	//		worldTransform_[0].translation_ += frontVec;
	//	}
	//	if (input_->PushKey(DIK_S)) {
	//		worldTransform_[0].translation_ += behindVec;
	//	}
	//	if (input_->PushKey(DIK_A)) {
	//		worldTransform_[0].translation_ += leftVec;
	//	}
	//	if (input_->PushKey(DIK_D)) {
	//		worldTransform_[0].translation_ += rightVec;
	//	}

	//	if (input_->PushKey(DIK_R)) {
	//		worldTransform_[0].translation_ += yTmpVec;
	//	}
	//	if (input_->PushKey(DIK_F)) {
	//		worldTransform_[0].translation_ += downVec;
	//	}

		////回転
		//if (input_->PushKey(DIK_I)) {
		//	viewProjection_.eye.z += 1;
		//}
		//if (input_->PushKey(DIK_K)) {
		//	viewProjection_.eye.z -= 1;
		//}
		//if (input_->PushKey(DIK_J)) {
		//	viewProjection_.eye.x -= 1;
		//}
		//if (input_->PushKey(DIK_L)) {
		//	viewProjection_.eye.x += 1;
		//}

		//if (input_->PushKey(DIK_LEFT)) {
		//	viewProjection_.target.x -= 1;
		//}
		//if (input_->PushKey(DIK_RIGHT)) {
		//	viewProjection_.target.x += 1;
		//}
		//viewProjection_.UpdateMatrix();

	//	break;

	//case 2:
	//	if (input_->TriggerKey(DIK_Q)) {
	//		scene = 3;
	//	}

	//	if (input_->PushKey(DIK_A)) {
	//		scaleX += 0.05f;
	//	}
	//	if (input_->PushKey(DIK_Z)) {
	//		scaleX -= 0.05f;
	//	}

	//	if (input_->PushKey(DIK_W)) {
	//		scaleY += 0.05f;
	//	}
	//	if (input_->PushKey(DIK_S)) {
	//		scaleY -= 0.05f;
	//	}

	//	if (input_->PushKey(DIK_E)) {
	//		scaleZ += 0.05f;
	//	}
	//	if (input_->PushKey(DIK_D)) {
	//		scaleZ -= 0.05f;
	//	}
	//	break;

	//case 3:
	//	if (input_->TriggerKey(DIK_Q)) {
	//		scene = 0;
	//	}

	//	//回転
	//	if (input_->PushKey(DIK_LEFT)) {
	//		worldTransform_[0].rotation_.y -= kRotSpeed;
	//	}
	//	if (input_->PushKey(DIK_RIGHT)) {
	//		worldTransform_[0].rotation_.y += kRotSpeed;
	//	}

	//	if (input_->PushKey(DIK_DOWN)) {
	//		worldTransform_[0].rotation_.x -= kRotSpeed;
	//	}
	//	if (input_->PushKey(DIK_UP)) {
	//		worldTransform_[0].rotation_.x += kRotSpeed;
	//	}

	//	if (input_->PushKey(DIK_D)) {
	//		worldTransform_[0].rotation_.z -= kRotSpeed;
	//	}
	//	if (input_->PushKey(DIK_A)) {
	//		worldTransform_[0].rotation_.z += kRotSpeed;
	//	}
	//	break;
	//}

	////スケーリング
	//Matrix4 matScale;
	//worldTransform_[0].scale_ = { scaleX,scaleY,scaleZ };

	//matScale.m[0][0] = worldTransform_[0].scale_.x;
	//matScale.m[1][1] = worldTransform_[0].scale_.y;
	//matScale.m[2][2] = worldTransform_[0].scale_.z;
	//matScale.m[3][3] = 1;

	////X軸回転
	//Matrix4 matRotX;

	//matRotX.m[0][0] = 1;
	//matRotX.m[1][1] = cos(worldTransform_[0].rotation_.x);
	//matRotX.m[1][2] = sin(worldTransform_[0].rotation_.x);
	//matRotX.m[2][1] = -sin(worldTransform_[0].rotation_.x);
	//matRotX.m[2][2] = cos(worldTransform_[0].rotation_.x);
	//matRotX.m[3][3] = 1;


	////Y軸回転
	//Matrix4 matRotY;

	//matRotY.m[0][0] = cos(worldTransform_[0].rotation_.y);
	//matRotY.m[1][1] = 1;
	//matRotY.m[0][2] = -sin(worldTransform_[0].rotation_.y);
	//matRotY.m[2][0] = sin(worldTransform_[0].rotation_.y);
	//matRotY.m[2][2] = cos(worldTransform_[0].rotation_.y);
	//matRotY.m[3][3] = 1;

	////Z軸回転
	//Matrix4 matRotZ;

	//matRotZ.m[0][0] = cos(worldTransform_[0].rotation_.z);
	//matRotZ.m[0][1] = sin(worldTransform_[0].rotation_.z);
	//matRotZ.m[1][0] = -sin(worldTransform_[0].rotation_.z);
	//matRotZ.m[1][1] = cos(worldTransform_[0].rotation_.z);
	//matRotZ.m[2][2] = 1;
	//matRotZ.m[3][3] = 1;

	//平行移動

	for (int i = 0; i < 2; i++) {
		matTrans[i] = MathUtility::Matrix4Identity();

		matTrans[i].m[0][0] = 1;
		matTrans[i].m[1][1] = 1;
		matTrans[i].m[2][2] = 1;
		matTrans[i].m[3][0] = worldTransform_[i].translation_.x;
		matTrans[i].m[3][1] = worldTransform_[i].translation_.y;
		matTrans[i].m[3][2] = worldTransform_[i].translation_.z;
		matTrans[i].m[3][3] = 1;

	}

	//掛け算して代入
	for (int i = 0; i < 2; i++) {
		worldTransform_[i].matWorld_ = matTrans[i];
	}

	//行列を転送する
	for (int i = 0; i < 2; i++) {
		worldTransform_[i].TransferMatrix();
	}


	/*for (int i = 2; i < 10; i++) {
		worldTransform_[i].matWorld_.m[0][0] = 2;
		worldTransform_[i].matWorld_.m[1][1] = 2;
		worldTransform_[i].matWorld_.m[2][2] = 2;
		worldTransform_[i].matWorld_.m[3][1] = -7;
		worldTransform_[i].matWorld_.m[3][2] = -35;
		worldTransform_[i].matWorld_.m[3][0] = -14 + (2.8 * i);
		worldTransform_[i].TransferMatrix();
	}
	for (int i = 10; i < 20; i++) {
		worldTransform_[i].matWorld_.m[0][0] = 2;
		worldTransform_[i].matWorld_.m[1][1] = 2;
		worldTransform_[i].matWorld_.m[2][2] = 2;
		worldTransform_[i].matWorld_.m[3][1] = 7;
		worldTransform_[i].matWorld_.m[3][2] = -35;
		worldTransform_[i].matWorld_.m[3][0] = -13 + (2.8 * (i - 10));
		worldTransform_[i].TransferMatrix();
	}*/

	debugText_->SetPos(0, 0);
	debugText_->Printf("%d", scene);

	/*debugCamera_->Update();*/
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//for (int i = 0; i < 2; i++) {
	//	model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	//}
	model_->Draw(worldTransform_[0], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[1], viewProjection_, mario);

	PrimitiveDrawer::GetInstance()->DrawLine3d(worldTransform_[0].translation_, point,Vector4(1,0,0,1));
	/*PrimitiveDrawer::GetInstance()->DrawLine3d(worldTransform_[0].translation_, worldTransform_[1].translation_, Vector4(1, 1, 1, 1));*/
	
	//for (int i = 0; i < 100; i++) {
	//	PrimitiveDrawer::GetInstance()->DrawLine3d(p1[i], p2[i], redNum);
	//	PrimitiveDrawer::GetInstance()->DrawLine3d(p3[i], p4[i], blueNum);
	//}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

float Radian(float num) {
	const float PI = 3.141592;
	return num * PI / 180;
}