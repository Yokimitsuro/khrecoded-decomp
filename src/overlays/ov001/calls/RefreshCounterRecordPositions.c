#include "nitro/types.h"

extern u32 data_ov001_0209e000;
extern u32 data_ov001_0209e010;
extern u32 GetSceneTagTracker();
extern u32 FindActiveRecordById();
extern u32 func_ov027_020b8200();
extern u32 func_ov027_020b8230();

void RefreshCounterRecordPositions(int counter)

{
  u32 container;
  u32 record;
  
  container = GetSceneTagTracker();
  record = FindActiveRecordById
                    (container,*(u32 *)((u8 *)&data_ov001_0209e010 +
                                    (u32)*(u16 *)(counter + *(int *)(counter + 0x2c) * 2 + 0x20)
                                    * 4) & 0xffff);
  func_ov027_020b8200(container,record,0xf);
  func_ov027_020b8230(container,record);
  record = FindActiveRecordById
                    (container,*(u32 *)((u8 *)&data_ov001_0209e000 +
                                    (u32)*(u16 *)
                                           (counter + (*(u32 *)(counter + 0x2c) ^ 1) * 2 + 0x20) *
                                    4) & 0xffff);
  func_ov027_020b8200(container,record,0x13);
  func_ov027_020b8230(container,record);
  return;
}
