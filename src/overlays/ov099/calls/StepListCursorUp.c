#include "nitro/types.h"

typedef struct ListState {
  int id;
  int pageSize;
  int itemCount;
  int slot;
  u8 pad_10[0x2c - 0x10];
  int scrollTop;
  int cursorRow;
  u8 pad_34[0x4c - 0x34];
} ListState;

typedef struct SlotPos {
  int x;
  int y;
  u8 pad_08[0xc];
} SlotPos;

typedef struct ViewerWork {
  u8 pad_0000[0xccc8];
  SlotPos topSlotPos[21];
  u8 pad_ce6c[0xd054 - 0xce6c];
  ListState lists[1];
} ViewerWork;

extern u16 data_02060500;
extern void SetSlotObjPosition(int screen, int slot, int posX, int posY, ViewerWork *work);
extern void func_ov099_020c11d4(int id, ViewerWork *work);

BOOL StepListCursorUp(int listIndex, ViewerWork *work) {
  ListState *list = &work->lists[listIndex];
  int row;
  SlotPos *pos;

  if (list->slot < 0) {
    list->cursorRow = 0;
  }
  row = list->cursorRow;
  if (list->scrollTop + row > 0) {
    if (row == 0) {
      list->scrollTop--;
    } else {
      list->cursorRow = row - 1;
      if (list->slot >= 0) {
        pos = &work->topSlotPos[list->slot];
        pos->y -= 16;
        SetSlotObjPosition(0, list->slot, pos->x, pos->y, work);
      }
    }
    func_ov099_020c11d4(list->id, work);
    return TRUE;
  }
  if (data_02060500 & 0x40) {
    list->cursorRow = list->pageSize - 1;
    list->scrollTop = list->itemCount - list->pageSize;
    if (list->slot >= 0) {
      pos = &work->topSlotPos[list->slot];
      pos->y += (list->pageSize - 1) * 16;
      SetSlotObjPosition(0, list->slot, pos->x, pos->y, work);
    }
    func_ov099_020c11d4(list->id, work);
    return TRUE;
  }
  return FALSE;
}
