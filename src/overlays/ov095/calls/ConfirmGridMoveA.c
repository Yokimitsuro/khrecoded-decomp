#include "nitro/types.h"

typedef struct {
    u8 pad[0x34];
    int scroll;
} GridTable;

typedef struct {
    u8 pad0[0x110a4];
    GridTable table;
    u8 pad1[0x11100 - 0x110a4 - sizeof(GridTable)];
    int direction;
} GridWork;

extern BOOL MoveGridCursorUp(GridWork *work);
extern void LayoutTabEntries(GridWork *work);
extern void func_ov095_020bfa38(int mode, GridWork *work);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void SetPanelMode_020c1210(int mode, GridWork *work);

void ConfirmGridMoveA(GridWork *work) {
    GridTable *table;

    if (!MoveGridCursorUp(work)) {
        return;
    }
    table = &work->table;
    if (table->scroll < 0x100) {
        work->direction = 0;
    }
    if (table->scroll > 0x100) {
        work->direction = 1;
    }
    LayoutTabEntries(work);
    func_ov095_020bfa38(-1, work);
    PlaySoundEffect(0, 0);
    SetPanelMode_020c1210(2, work);
}