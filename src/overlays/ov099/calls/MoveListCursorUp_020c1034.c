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

extern void SetSlotObjPosition(int id, int slot, int posX, int posY, ViewerWork *work);
extern void func_ov099_020c11d4(int id, ViewerWork *work);

BOOL MoveListCursorUp_020c1034(int listIndex, ViewerWork *work) {
  ListState *list = &work->lists[listIndex];
  int scrollTop = list->scrollTop;
  int newTop;
  SlotPos *pos;

  if (scrollTop == 0) {
    if (list->cursorRow == 0) {
      return FALSE;
    }
    list->cursorRow = 0;
    if (list->slot >= 0) {
      pos = &work->topSlotPos[list->slot];
      pos->y = 0x28;
      SetSlotObjPosition(list->id, list->slot, pos->x, pos->y, work);
    }
    func_ov099_020c11d4(list->id, work);
    return TRUE;
  }
  newTop = scrollTop - list->pageSize;
  if (list->slot < 0) {
    list->cursorRow = 0;
  }
  if (newTop < 0) {
    list->scrollTop = 0;
  } else {
    list->scrollTop = newTop;
  }
  func_ov099_020c11d4(list->id, work);
  return TRUE;
}
