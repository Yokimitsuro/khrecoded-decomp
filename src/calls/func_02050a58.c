#include "nitro/types.h"

extern int *gMapLayout;
extern int NNSi_FndFreeFromDefaultHeap();

void func_02050a58(void) {
  int *block;
  int references;

  block = gMapLayout;
  if ((gMapLayout != (int *)0x0) &&
     (references = *gMapLayout, *gMapLayout = references + -1, references + -1 == 0)) {
    if ((void *)block[0x27] != (void *)0x0) {
      NNSi_FndFreeFromDefaultHeap((void *)block[0x27]);
      block[0x27] = 0;
    }
    NNSi_FndFreeFromDefaultHeap(block);
    gMapLayout = (int *)0x0;
  }
}
