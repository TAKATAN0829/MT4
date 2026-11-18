#define NOMINMAX
#include <Novice.h>
#include "Vector2.h"
#include <numbers>
#include "MT4.h"
#include <algorithm>
#include <imgui.h>
#include <chrono>
#include <cmath>

const char kWindowTitle[] = "LE2B_09_コウサカ_タカフミ";

const float halfPi = std::numbers::pi_v<float> / 2.f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
	
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		// 回転の球面線形補間
		Quaternion rotation0 = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 0.71f, 0.71f, 0.0f }), 0.3f);
		Quaternion rotation1 = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 0.71f, 0.0f, 0.71f }), 3.141592f);

		Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0, 0, interpolate0, " : interpolate0, Slerp(q0, q1, 0.0f)");
		QuaternionScreenPrintf(0, kRowHeight, interpolate1, " : interpolate1, Slerp(q0, q1, 0.3f)");
		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2, " : interpolate2, Slerp(q0, q1, 0.5f)");
		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3, " : interpolate3, Slerp(q0, q1, 0.7f)");
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4, " : interpolate4, Slerp(q0, q1, 1.0f)");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
