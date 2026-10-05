#include "nitro/types.h"

typedef struct {
    u32 first;
    u32 second;
} TileRange;

typedef struct {
    TileRange *range;
    u32 width;
    u32 height;
    u32 flags;
} TileTableDesc;

extern const TileRange data_ov086_020c20f4;
extern const TileTableDesc data_ov086_020c2118;
extern void InitTileTableFrom(void *table, const TileTableDesc *source);

void InitRecordTileTable(u8 *menu)
{
    TileRange range = data_ov086_020c20f4;
    TileTableDesc desc = data_ov086_020c2118;

    desc.range = &range;
    InitTileTableFrom(menu + 0x174, &desc);
}
