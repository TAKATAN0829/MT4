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

	// 円A
	Vector2 circleA{ 0.0f, 0.0f };
	const float radiusA = 12.0f;

	// 円B
	Vector2 circleB{ 640.0f, 360.0f };
	const float radiusB = 20.0f;

	// 追従速度
	float speed = 6.0f;

	const float kDeltaTime = 1.0f / 60.0f;

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

		int mouseX = 0;
		int mouseY = 0;
		Novice::GetMousePosition(&mouseX, &mouseY);
		circleA = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

		float t = speed * kDeltaTime;
		circleB.x += t * (circleA.x - circleB.x);
		circleB.y += t * (circleA.y - circleB.y);

#ifdef USE_IMGUI
		ImGui::Begin("Follow");
		ImGui::SliderFloat("speed", &speed, 0.0f, 60.0f);
		ImGui::End();
#endif
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(
			static_cast<int>(circleA.x), static_cast<int>(circleA.y),
			static_cast<int>(radiusA), static_cast<int>(radiusA),
			0.0f, RED, kFillModeSolid);
		
		Novice::DrawEllipse(
			static_cast<int>(circleB.x), static_cast<int>(circleB.y),
			static_cast<int>(radiusB), static_cast<int>(radiusB),
			0.0f, GREEN, kFillModeSolid);

		Novice::DrawLine(
			static_cast<int>(circleA.x), static_cast<int>(circleA.y),
			static_cast<int>(circleB.x), static_cast<int>(circleB.y),
			WHITE);


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
