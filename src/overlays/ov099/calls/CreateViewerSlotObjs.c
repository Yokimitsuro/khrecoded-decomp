#include "nitro/types.h"

typedef struct ObjManager {
  u8 data[0x6434];
} ObjManager;

typedef struct SlotObjDesc {
  int resource;
  int cell;
  int posX;
  int posY;
  int priority;
  int hidden;
} SlotObjDesc;

typedef struct ObjManagerConfig {
  u32 fileId;
  int type;
  int reserved0;
  int reserved1;
} ObjManagerConfig;

typedef struct ViewerWork {
  u8 pad_000[0x300];
  u32 archiveA;
  u32 archiveB;
  u32 archiveC;
  u8 pad_30c[0x45c - 0x30c];
  ObjManager objManagers[2];
} ViewerWork;

extern SlotObjDesc data_ov099_020c257c[];
extern SlotObjDesc data_ov099_020c23ac[];
extern void InitObjManager(ObjManager *manager, ObjManagerConfig *config);
extern void PXI_Init_0204f020(ObjManager *manager, u32 fileId);
extern void CreateSlotObj(int screen, int slot, SlotObjDesc *desc, ViewerWork *work);
extern BOOL IsEntryFlagSet_020c16ac(int list, int index);
extern void SetSlotObjVisible(int screen, int slot, int visible, ViewerWork *work);
extern void RefreshSlotObj(int screen, int slot, u32 value, ViewerWork *work);

#define ARCHIVE_FILE_ID(archive) ((((archive) + 0x8000) & 0xfffffc) << 7)

void CreateViewerSlotObjs(ViewerWork *work) {
  BOOL seen;
  BOOL isNew;
  int slot;
  int subSlot;
  int row;
  ObjManagerConfig config;

  config.fileId = ARCHIVE_FILE_ID(work->archiveA) | 0x80000003;
  config.type = 1;
  config.reserved0 = 0;
  config.reserved1 = 0;
  InitObjManager(&work->objManagers[0], &config);
  PXI_Init_0204f020(&work->objManagers[0], ARCHIVE_FILE_ID(work->archiveC) | 0x80000000);
  for (slot = 0; slot < 0x15; slot++) {
    CreateSlotObj(0, slot, &data_ov099_020c257c[slot], work);
  }
  for (row = 0; row < 9; row++) {
    seen = IsEntryFlagSet_020c16ac(1, row);
    isNew = IsEntryFlagSet_020c16ac(2, row) != 0;
    SetSlotObjVisible(0, row + 0xc, seen, work);
    RefreshSlotObj(0, row + 0xc, isNew, work);
  }
  config.fileId = ARCHIVE_FILE_ID(work->archiveA) | 0x80000001;
  config.type = 2;
  config.reserved0 = 0;
  config.reserved1 = 0;
  InitObjManager(&work->objManagers[1], &config);
  for (subSlot = 0; subSlot < 6; subSlot++) {
    CreateSlotObj(1, subSlot, &data_ov099_020c23ac[subSlot], work);
  }
}
