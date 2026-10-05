#include "nitro/types.h"

typedef unsigned int code();

void ApplyScalarToVec3(unsigned int *values,code *transform) {
  unsigned int value;

  value = (*transform)(*values);
  *values = value;
  value = (*transform)(values[1]);
  values[1] = value;
  value = (*transform)(values[2]);
  values[2] = value;
}
