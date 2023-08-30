
#include <assert.h>
#include "MATHEX.h"




void WorldTransform::UpdateMatrix() {

	//スケール、回転、平行移動
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
    
	//if (parent_) 
	//{
	//	Add(matWorld_, parent_->matWorld_);
	//}

	//定数バッファに転送
	TransferMatrix();

	if (parent_)
	{
		Multiply( matWorld_, parent_->matWorld_);

	}

}


