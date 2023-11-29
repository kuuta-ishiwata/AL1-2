#pragma once
#include <Model.h>
#include <WorldTransform.h>
#include "MATHEX.h"
#include "FollowCamera.h"


class RailCamera 
{
public:
	///< summary>
	/// 初期化
	///</summary>
	void Initialize();

	///< summary>
	/// 更新
	///</summary>

	void Update();

	 const ViewProjection& GetViewProjection() { return viewprojection_; }
	 const WorldTransform& GetworldTransform()  { return worldtransform_; }


private:
	WorldTransform worldtransform_;
	Model* model = nullptr;

	ViewProjection viewprojection_;

};


