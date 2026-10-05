#include "nitro/types.h"

u32 IsFieldStateAvailable(int *entry)

{
  if ((entry[1] == 4) && (*(u8 *)(*(int *)(*entry + 0x14) + 0x194) == '\0')) {
    return 0;
  }
  return 1;
}
