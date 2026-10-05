#include "nitro/types.h"

extern u32 func_ov027_020b8200();
extern u32 func_ov027_020b8230();

void PositionListRecords(u32 container,int list,u32 position)

{
  int recordIndex;
  
  recordIndex = 0;
  if ((int)*(u16 *)(list + 2) > 0) {
    do {
      func_ov027_020b8200(container,*(u32 *)(*(int *)(list + 0x2c) + recordIndex * 4),position);
      recordIndex = recordIndex + 1;
    } while (recordIndex < (int)(u32)*(u16 *)(list + 2));
  }
  func_ov027_020b8230(container,*(u32 *)
                               (*(int *)(list + 0x2c) + (u32)*(u16 *)(list + 4) * 4));
  return;
}
