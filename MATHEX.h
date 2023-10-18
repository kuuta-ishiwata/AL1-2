#pragma once
#include "Player.h"
#include <assert.h>
#include <ImGuiManager.h>


Vector3 Add(const Vector3 v1, const Vector3& v2);


Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Vector3 Multiply2(const float& v1, const Vector3& v2);

// スケーリング行列を宣言
Matrix4x4 matScale(const Vector3 scale);


Matrix4x4 matRotX(float rotation);


Matrix4x4 matRotY(float rotation);

Matrix4x4 matRotZ(float rotation);

Matrix4x4 matRotXYZ(float rotationX, float rotationY, float rotationZ);

    // 平行移動行列を宣言
 Matrix4x4 matTrans(const Vector3 translation);





Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

Vector3 Normalize(const Vector3& v);

Matrix4x4 Transpose(const Matrix4x4& m);