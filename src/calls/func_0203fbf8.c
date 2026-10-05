#include "nitro/types.h"

extern u32 UpdatePenetrationDepth();
extern u32 VEC_DotProduct();

void func_0203fbf8(int extent,void *offset,void *axis,u8 feature,void *result) {
  int distance;

  distance = VEC_DotProduct(axis,offset);
  UpdatePenetrationDepth(extent,distance,axis,feature,result);
}
