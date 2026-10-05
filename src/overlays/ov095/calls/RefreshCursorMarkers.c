#include "nitro/types.h"

typedef struct {
    u8 pad0[4];
    int firstMarker;
    int secondMarker;
    u8 pad1[0x34 - 0xc];
    int scroll;
} GridTable;

typedef struct {
    u8 pad[0x110a4];
    GridTable table;
} GridWork;

extern void SetGridEntryVisible(int layer, int index, int visible, GridWork *work);

void RefreshCursorMarkers(GridWork *work) {
    GridTable *table = &work->table;

    if (table->firstMarker >= 0) {
        if (table->scroll == 0) {
            SetGridEntryVisible(0, table->firstMarker, 0, work);
        } else {
            SetGridEntryVisible(0, table->firstMarker, 1, work);
        }
    }
    if (table->secondMarker < 0) {
        return;
    }
    if (table->scroll >= 0x1fa) {
        SetGridEntryVisible(0, table->secondMarker, 0, work);
    } else {
        SetGridEntryVisible(0, table->secondMarker, 1, work);
    }
}