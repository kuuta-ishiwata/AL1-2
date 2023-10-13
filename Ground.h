#pragma once
#include <Model.h>
#include <WorldTransform.h>

class Ground {

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:

	// ワールド変更データ
	WorldTransform worldtransform_;

	// モデル
	Model* model_ = nullptr;

	ViewProjection viewprojection_;




};
