#include <Novice.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <assert.h>

const char kWindowTitle[] = "LE2D_20_フルヤユウト";

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

//平行移動行列
Matrix4x4  MakeTranslateMatrix(const Vector3& translate) {};

//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {};

//座標返還
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {};


// --- 描画用関数 ---
static const int kColumnWidth = 60;
static const int kRowHeight = 20;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}


void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth,
				y + (row + 1) * kRowHeight,
				"%6.02f", matrix.m[row][column]
			);
		}
	}
}

// WinMain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Novice::Initialize(kWindowTitle, 1280, 720);

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 translate{ 4.1f, 2.6f, 0.8f };
	Vector3 scale{ 1.5f, 5.2f, 7.3f };
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Vector3 point{ 2.3f,3.8f,1.4f };
	Matrix4x4 transformMatrix = {
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};
	Vector3 transformed = Transform(point, transformMatrix);


	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();

		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		Vector3 translate{ 4.1f, 2.6f, 0.8f };
		Vector3 scale{ 1.5f, 5.2f, 7.3f };
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
		Vector3 point{ 2.3f,3.8f,1.4f };
		Matrix4x4 transformMatrix = {
			1.0f,2.0f,3.0f,4.0f,
			3.0f,1.0f,1.0f,2.0f,
			1.0f,4.0f,2.0f,3.0f,
			2.0f,2.0f,1.0f,3.0f
		};
		Vector3 transformed = Transform(point, transformMatrix);


		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, 0, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, scaleMatrix, "scaleMatrix");


		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}
