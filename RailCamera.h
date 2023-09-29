﻿#pragma once
#include <Model.h>
#include <WorldTransform.h>


///<summary>
///レールカメラ
///</summary>


class RailCamera
{

public:
	///< summary>
	/// 初期化
	///</summary>
	void Initialize(Vector3 position);

	///< summary>
	/// 更新
	///</summary>

	void Update();


	ViewProjection GetViewProjection() { return viewprojection_; }
	const WorldTransform& GetworldTransform() const { return worldtransform_; }

	
private:

	WorldTransform worldtransform_;
	Model* model = nullptr;

	ViewProjection viewprojection_;



};

