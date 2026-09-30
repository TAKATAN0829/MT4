#define NOMINMAX
#include <Novice.h>
#include "Vector2.h"
#include <numbers>
#include "MT4.h"
#include <algorithm>
#include <imgui.h>

const char kWindowTitle[] = "LE2B_09_コウサカ_タカフミ";

const float halfPi = std::numbers::pi_v<float> / 2.f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	Spherical s{ 6.f,0.f,halfPi };
	Vector3 pos = ToCartesian(s);

	Vector3 target = { 0.f,0.f,0.f };


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

		Vector3 eye = target + ToCartesian(s);

		Vector3 worldUp{ 0.f,1.f,0.f };
		Vector3 forward = Normalize(target - eye);
		Vector3 right = Normalize(Cross(worldUp, forward));
		Vector3 up = Cross(forward, right);

		Matrix4x4 cameraMatrix{ {
			{right.x,right.y,right.z,0.f},
			{up.x,up.y,up.z,0.f},
			{forward.x,forward.y,forward.z,0.f},
			{eye.x,eye.y,eye.z,1.f}
		} };

		const float limit =
			std::numbers::pi_v<float> / 2.f - 0.01f;
		s.radius = (std::max)(s.radius, 0.1f);
		s.theta = std::clamp(s.theta, -limit, limit);

#ifdef USE_IMGUI
		ImGui::Begin("Camera");

		ImGui::DragFloat3("target", &target.x, 0.01f);
		ImGui::Separator();

		ImGui::DragFloat("radius", &s.radius, 0.01f, 0.1f, 100.0f);
		ImGui::SliderFloat("theta", &s.theta, -limit, limit);
		ImGui::DragFloat("phi", &s.phi, 0.01f);
		ImGui::Separator();

		ImGui::Text("eye     : %.2f, %.2f, %.2f", eye.x, eye.y, eye.z);
		ImGui::Text("forward : %.2f, %.2f, %.2f", forward.x, forward.y, forward.z);
		ImGui::Text("right   : %.2f, %.2f, %.2f", right.x, right.y, right.z);
		ImGui::Text("up      : %.2f, %.2f, %.2f", up.x, up.y, up.z);
		ImGui::Separator();

		ImGui::Text("cameraMatrix");
		for (int row = 0; row < 4; ++row) {
			ImGui::Text("%6.2f %6.2f %6.2f %6.2f",
				cameraMatrix.m[row][0], cameraMatrix.m[row][1], cameraMatrix.m[row][2], cameraMatrix.m[row][3]);
		}

		ImGui::End();
#endif

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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
