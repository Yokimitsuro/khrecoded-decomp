#include "nitro/types.h"

extern char sOv099_UiReportEnmmdlP2_020c288c[];
extern u32 Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern int *Archive_LoadFile(u32 fileId, u32 param2);

void LoadViewerModelTable(u32 *viewer) {
  int index;
  u32 header;
  int *table;

  header = Msg_OpenContainerAndReadHeader(sOv099_UiReportEnmmdlP2_020c288c, 0xe, 0);
  viewer[0x29] = header;
  table = Archive_LoadFile(((header + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0xe);
  viewer[0] = (u32)table;
  for (index = 0; index < 0x28; index++) {
    viewer[index + 1] = (u32)table;
    table = table + *table + 1;
  }
}
