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
		// 今回の先頭時刻との差から秒（float）を算出

		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Vector3 from0 = Normalize(Vector3{ 1.0f, 0.7f, 0.5f });
		Vector3 to0 = -from0;
		Vector3 from1 = Normalize(Vector3{ -0.6f, 0.9f, 0.2f });
		Vector3 to1 = Normalize(Vector3{ 0.4f, 0.7f, -0.5f });
		Matrix4x4 rotateMatrix0 = MakeRotateMatrix(DirectionToDirection(
			Normalize(Vector3{ 1.0f, 0.0f, 0.0f }),
			Normalize(Vector3{ -1.0f, 0.0f, 0.0f })));
		Matrix4x4 rotateMatrix1 = MakeRotateMatrix(DirectionToDirection(from0, to0));
		Matrix4x4 rotateMatrix2 = MakeRotateMatrix(DirectionToDirection(from1, to1));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, rotateMatrix0, "rotateMatrix0");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateMatrix1, "rotateMatrix1");
		MatrixScreenPrintf(0, kRowHeight * 10, rotateMatrix2, "rotateMatrix2");

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
