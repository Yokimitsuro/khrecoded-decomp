#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int origin;
    int firstMarker;
    int secondMarker;
    int width;
    int height;
} GridConfig;

typedef struct {
    int origin;
    int firstMarker;
    int secondMarker;
    int offsetX;
    int offsetY;
    fx32 scale;
    u8 pad[8];
    int *cells;
    int width;
    int height;
    int count;
    int cursor;
    int scroll;
    int viewTop;
    int viewBottom;
    int velocity;
} GridTable;

typedef struct {
    u8 pad[0x110a4];
    GridTable table;
} GridWork;

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void RefreshCursorMarkers(GridWork *work);

void InitGridTable(GridConfig *config, GridWork *work) {
    GridTable *table;

    work->table.origin = config->origin;
    table = &work->table;
    table->firstMarker = config->firstMarker;
    table->secondMarker = config->secondMarker;
    table->offsetX = 0;
    table->offsetY = 0;
    table->scale = 0x1000;
    table->width = config->width;
    table->height = config->height;
    table->count = table->width * table->height;
    table->cursor = 0;
    table->scroll = 0;
    table->viewTop = 0x60;
    table->viewBottom = 0x90;
    table->velocity = 0;
    table->cells = NNS_FndAllocFromDefaultExpHeapEx(table->count * 4, -4);
    MIi_CpuClearFast(0, table->cells, table->count * 4);
    RefreshCursorMarkers(work);
}