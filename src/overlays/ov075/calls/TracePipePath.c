#include "nitro/types.h"

typedef struct PipeTile {
    u16 cell;
    u8 kind;
    s8 linkId;
} PipeTile;

typedef struct GridInfo {
    u8 width;
} GridInfo;

typedef struct PipeBoard {
    u8 pad_0000[0x18];
    void *linkTargets[(0x98 - 0x18) / 4];
    GridInfo *grid;
    PipeTile *tiles[(0x2be8 - 0x9c) / 4];
    u8 cellLevels[1];
} PipeBoard;

typedef struct SaveData {
    u8 pad_0000[0x2c5c];
    u8 linkFlags[0x2c67 - 0x2c5c];
    u8 level;
} SaveData;

extern SaveData *data_0205fe0c;
extern int GetPackedBitMask(void *bits, int index);

BOOL TracePipePath(PipeBoard *board, PipeTile *tile, int dir, void **out)
{
    PipeTile **tiles = board->tiles;
    int index;
    u8 width;
    u8 kind;
    int entryKind;

    if (tile == NULL) {
        return FALSE;
    }
    entryKind = tile->kind;
    if (entryKind < 0xe || entryKind == 0x19) {
        return FALSE;
    }
    switch (dir) {
    case 0:
        if (entryKind == 0xe || entryKind == 0x11 || entryKind == 0x14) {
            return FALSE;
        }
        break;
    case 1:
        if (entryKind == 0xe || entryKind == 0xf || entryKind == 0x15) {
            return FALSE;
        }
        break;
    case 2:
        if (entryKind == 0xf || entryKind == 0x10 || entryKind == 0x16) {
            return FALSE;
        }
        break;
    case 3:
        if (entryKind == 0x11 || entryKind == 0x10 || entryKind == 0x17) {
            return FALSE;
        }
        break;
    }
    index = 0;
    width = board->grid->width;
    for (;;) {
        if (tile == NULL) {
            return FALSE;
        }
        if (tile->linkId >= 0 && !(GetPackedBitMask(data_0205fe0c->linkFlags, tile->linkId) ? TRUE : FALSE)) {
            if (board->cellLevels[tile->cell] <= data_0205fe0c->level) {
                *out = board->linkTargets[tile->linkId];
                return TRUE;
            }
            return FALSE;
        }
        kind = tile->kind;
        if (kind < 0xe || kind > 0x13) {
            *out = tile;
            return TRUE;
        }
        switch (dir) {
        case 0:
            if (kind == 0xf) {
                index = (s16)(tile->cell - width);
                dir = 1;
            } else if (kind == 0x10) {
                index = (s16)(tile->cell + width);
                dir = 3;
            } else {
                index = (s16)(tile->cell - 1);
                dir = 0;
            }
            break;
        case 1:
            if (kind == 0x11) {
                index = (s16)(tile->cell - 1);
                dir = 0;
            } else if (kind == 0x10) {
                index = (s16)(tile->cell + 1);
                dir = 2;
            } else {
                index = (s16)(tile->cell - width);
                dir = 1;
            }
            break;
        case 2:
            if (kind == 0xe) {
                index = (s16)(tile->cell - width);
                dir = 1;
            } else if (kind == 0x11) {
                index = (s16)(tile->cell + width);
                dir = 3;
            } else {
                index = (s16)(tile->cell + 1);
                dir = 2;
            }
            break;
        case 3:
            if (kind == 0xe) {
                index = (s16)(tile->cell - 1);
                dir = 0;
            } else if (kind == 0xf) {
                index = (s16)(tile->cell + 1);
                dir = 2;
            } else {
                index = (s16)(tile->cell + width);
                dir = 3;
            }
            break;
        }
        tile = tiles[index];
    }
}
