#include "nitro/types.h"

extern u32 func_0202a9e4();
extern char *GetRecordTableDEntry();
extern u32 CopyWideStringBounded();
extern u32 FillCategoryRecords();

void InitPanelRecordFromProfile(int context,int value)

{
  char *profileOrIndex;
  u8 variant;
  int randomValue;
  u32 chance;
  int entryAddress;
  
  randomValue = func_0202a9e4(0x32);
  profileOrIndex = GetRecordTableDEntry();
  CopyWideStringBounded(context + 0x10,*(u32 *)(profileOrIndex + 0x38),10);
  CopyWideStringBounded(context + 0x26,*(u32 *)(profileOrIndex + 0x3c),0x1a);
  if (*(short *)(profileOrIndex + 4) != -1) {
    *(char *)(context + 0x65) = (char)*(short *)(profileOrIndex + 4);
  }
  if (*(short *)(profileOrIndex + 6) != -1) {
    *(char *)(context + 0x66) = (char)*(short *)(profileOrIndex + 6);
  }
  if (*(short *)(profileOrIndex + 8) != -1) {
    *(char *)(context + 0x67) = (char)*(short *)(profileOrIndex + 8);
  }
  if (*(short *)(profileOrIndex + 10) != -1) {
    *(char *)(context + 0x68) = (char)*(short *)(profileOrIndex + 10);
  }
  *(u8 *)(context + 0x6c) = 2;
  FillCategoryRecords(context,profileOrIndex);
  chance = func_0202a9e4(1000);
  if (chance < 10) {
    *(u8 *)(context + 100) = 1;
  }
  variant = func_0202a9e4(9);
  *(u8 *)(context + 0x6b) = variant;
  if (value == 1) {
    *(u8 *)(context + 0x5e) = randomValue;
    for (int index = 1; index < 6; index++) {
      *(u8 *)(context + index + 0x5e) = 0xff;
    }
    return;
  }
  return;
}
