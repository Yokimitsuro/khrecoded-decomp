#include "nitro/types.h"

typedef struct MapCell {
    u16 cell;
    u8 type;
    s8 link;
    s16 param;
    u16 group;
    u8 flag;
    u8 pad_09[0xb];
} MapCell;

typedef struct MapFile {
    u8 width;
    u8 pad_01[3];
    u16 cellCount;
    u8 pad_06[2];
    MapCell cells[1];
} MapFile;

typedef struct MapLayout {
    int refCount;
    int linkCount;
    u16 anchorCells[10];
    MapCell *links[32];
    MapFile *file;
    MapCell *grid[0x6c0];
    MapCell *cellList[0x190];
    MapCell *groupCells[6][16];
    int unk_2360[24];
    u8 pad_23C0[0x120];
    u8 unk_24E0[0x40];
    u8 groupCounts[12];
    u8 cellOrder[0x6c0];
    u8 cellAttributes[0x6c0];
    u8 pad_32AC[0x108];
    int type6Count;
} MapLayout;

typedef struct GameState {
    u8 pad_0000[0x2878];
    u32 mapMode : 2;
    u32 unk_2878 : 30;
    u8 pad_287C[0x3e6];
    u8 mapModeSource;
    u8 pad_2C63[0xa];
    s8 cellParams[1];
} GameState;

extern MapLayout *gMapLayout;
extern GameState *data_0205fe0c;
extern const char sMain_UiSmxMapZ_02056188[];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *Archive_LoadFile(const char *path, u32 flags);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void OS_Terminate(void);
extern void FillGridRegion(MapCell **grid, MapCell *cell, int stride, int start, u32 width, u32 height);

int *AcquireMapLayout(BOOL reload, BOOL discard)
{
    MapLayout *map;
    BOOL isNew;
    MapFile *file;
    MapCell *cell;
    s16 linkIndex;
    MapCell *link;
    MapCell **linkSlot;
    s16 id;
    u16 group;
    u32 width;
    u32 height;
    MapCell **list;
    u16 remaining;
    u16 anchorCount;
    u8 order;
    u8 *cellOrder;
    int savedRefCount;
    s8 *params;
    int swap;

    if (discard) {
        map = NULL;
    } else {
        map = gMapLayout;
    }
    data_0205fe0c->mapMode = data_0205fe0c->mapModeSource;
    if (map == NULL || reload) {
        anchorCount = 0;
        order = 0;
        isNew = map == NULL;
        params = data_0205fe0c->cellParams;
        if (isNew) {
            map = NNSi_FndAllocFromDefaultHeap(sizeof(MapLayout));
            savedRefCount = 0;
        } else {
            savedRefCount = map->refCount;
        }
        list = map->cellList;
        if (isNew || map->refCount == 0) {
            file = NULL;
        } else {
            file = map->file;
        }
        func_01ff88c4(map, 0, sizeof(MapLayout));
        MI_CpuFill8(map->cellOrder, 0xff, 0x6c0);
        cellOrder = map->cellOrder;
        map->refCount = savedRefCount;
        if (isNew || reload) {
            if (file != NULL) {
                NNSi_FndFreeFromDefaultHeap(file);
            }
            file = Archive_LoadFile(sMain_UiSmxMapZ_02056188, 0x11);
        }
        map->file = file;
        cell = file->cells;
        for (remaining = file->cellCount; remaining != 0; remaining--, list++) {
            group = cell->group;
            *list = cell;
            map->grid[cell->cell] = cell;
            switch (cell->type) {
            case 3:
                map->anchorCells[cell->group] = cell->cell;
                height = 3;
                width = 3;
                anchorCount++;
                break;
            case 6:
                height = 2;
                width = 2;
                map->type6Count++;
                break;
            case 7:
                height = 3;
                width = 3;
                break;
            case 8:
                height = 2;
                width = 4;
                break;
            case 9:
                height = 5;
                width = 5;
                break;
            case 10:
                height = 2;
                width = 12;
                break;
            case 11:
                height = 6;
                width = 6;
                break;
            case 12:
                height = 5;
                width = 5;
                break;
            case 25:
                height = 2;
                width = 12;
                break;
            case 13:
                height = 6;
                width = 8;
                break;
            case 1:
                map->groupCells[group][map->groupCounts[group]++] = cell;
            default:
                width = 1;
                height = 1;
                if (cell->type < 14) {
                    cell->param = *params;
                    if (cell->param >= 0) {
                        cell->param += 0x90;
                        cell->flag = 0;
                    }
                    cellOrder[cell->cell] = order++;
                    params++;
                }
                break;
            }
            FillGridRegion(map->grid, cell, file->width, cell->cell, width, height);
            cell++;
        }
        if (*(u32 *)cell != 0x41424344 || anchorCount != 9) {
            OS_Terminate();
        }
        cell = (MapCell *)((u8 *)cell + 4);
        func_01ff8ad8(cell, map->unk_24E0, 0x40);
        cell = (MapCell *)((u8 *)cell + 0x40);
        func_01ff8ad8(cell, map->cellAttributes, 0x6c0);
        cell = (MapCell *)((u8 *)cell + 0x6c0);
        func_01ff8ad8(cell, map->groupCounts, 0xc);
        link = (MapCell *)((u8 *)cell + 0xc);
        linkSlot = map->links;
        for (linkIndex = 0; link->cell != 0; linkIndex++) {
            id = link->cell;
            link->type = link->link;
            if (map->grid[id] != NULL) {
                map->grid[id]->link = linkIndex;
            } else {
                map->grid[id] = link;
            }
            if (map->grid[(s16)(id + 1)] != NULL) {
                map->grid[(s16)(id + 1)]->link = linkIndex;
            } else {
                map->grid[(s16)(id + 1)] = link;
            }
            if (map->grid[(s16)(id + file->width)] != NULL) {
                map->grid[(s16)(id + file->width)]->link = linkIndex;
            } else {
                map->grid[(s16)(id + file->width)] = link;
            }
            if (map->grid[(s16)(id + file->width + 1)] != NULL) {
                map->grid[(s16)(id + file->width + 1)]->link = linkIndex;
            } else {
                map->grid[(s16)(id + file->width + 1)] = link;
            }
            *linkSlot++ = link;
            link++;
        }
        map->linkCount = linkIndex;
        swap = map->unk_2360[0];
        map->unk_2360[0] = map->unk_2360[1];
        map->unk_2360[1] = swap;
        swap = map->unk_2360[19];
        map->unk_2360[19] = map->unk_2360[22];
        map->unk_2360[22] = swap;
        swap = map->unk_2360[20];
        map->unk_2360[20] = map->unk_2360[21];
        map->unk_2360[21] = swap;
        gMapLayout = map;
    }
    map->refCount++;
    return &map->linkCount;
}
