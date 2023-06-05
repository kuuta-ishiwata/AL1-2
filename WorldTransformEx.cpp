
#include <assert.h>
#include "MATHEX.h"




void WorldTransform::UpdateMatrix() {

	//スケール、回転、平行移動
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
    
	//定数バッファに転送
	TransferMatrix();


}


