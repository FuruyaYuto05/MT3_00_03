#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <string.h> // memcpy に必要

const char kWindowTitle[] = "LE2D_20_フルヤユウト";

// ---------- 構造体定義 ----------
struct Vector3 {
    float x;
    float y;
    float z;
};

struct Matrix4x4 {
    float m[4][4];
};

// ---------- 行列関数の実装 ----------
// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        translate.x, translate.y, translate.z, 1
    };
}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
    return {
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    };
}

// ベクトルの座標変換
Vector3 Transform(const Vector3& v, const Matrix4x4& m) {
    Vector3 result{};
    result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
    result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
    result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
    return result;
}

// ---------- 描画用ユーティリティ ----------
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

// ---------- メイン関数 ----------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // データ
        Vector3 translate{ 4.1f, 2.6f, 0.8f };
        Vector3 scale{ 1.5f, 5.2f, 7.3f };
        Vector3 point{ 2.3f, 3.8f, 1.4f };

        Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
        Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

        // 列優先で定義（column-major）
        Matrix4x4 transformMatrix = {
            1.0f, 3.0f, 1.0f, 2.0f, // 列0
            2.0f, 1.0f, 4.0f, 2.0f, // 列1
            3.0f, 1.0f, 2.0f, 1.0f, // 列2
            4.0f, 2.0f, 3.0f, 3.0f  // 列3
        };

        Vector3 transformed = Transform(point, transformMatrix);

        // 描画
        VectorScreenPrintf(0, 0, transformed, "transformed");
        MatrixScreenPrintf(0, kRowHeight * 2, translateMatrix, "translateMatrix");
        MatrixScreenPrintf(0, kRowHeight * 8, scaleMatrix, "scaleMatrix");

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
