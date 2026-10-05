#include "nitro/types.h"

extern unsigned int *gRecordManager;
extern unsigned int Archive_LoadFile();
extern unsigned int func_0202c4a0();

void func_02051724(int alternateLoader,unsigned int unused,u32 loaderValue,u32 loaderExtra) {
  int *work;
  u32 resource;

  work = gRecordManager;
  if (alternateLoader != 0) {
    resource = func_0202c4a0((*gRecordManager + 0x8000U & 0xfffffc) << 7 | 0x80000003,0x11,loaderValue,
                          loaderExtra);
    work[0xc] = resource;
    return;
  }
  resource = Archive_LoadFile((*gRecordManager + 0x8000U & 0xfffffc) << 7 | 0x80000003,0x11,loaderValue,
                        loaderExtra);
  work[0xc] = resource;
}
