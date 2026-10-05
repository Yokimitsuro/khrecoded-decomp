#include "nitro/types.h"

extern u32 UpdateSignedPenetrationDepth();
extern u32 VEC_DotProduct();

void func_0203fbb8(int extent,void *offset,void *axis,u8 feature,void *result) {
  int distance;

  distance = VEC_DotProduct(axis,offset);
  UpdateSignedPenetrationDepth(extent,distance,axis,feature,result);
}
