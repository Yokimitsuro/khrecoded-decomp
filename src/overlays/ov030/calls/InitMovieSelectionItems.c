#include "nitro/types.h"

typedef struct {
    s16 kind;
    u8 pad_02[2];
    u8 level;
    u8 pad_05[7];
} SelectionItem;

typedef struct {
    SelectionItem items[21];
    u8 pad_fc[4];
    int count;
    s16 selection;
} SelectionList;

typedef struct {
    u8 pad_000[0x2c];
    SelectionList list;
} SelectionRecord;

typedef struct {
    int kind;
    int level;
} DefaultItem;

typedef struct {
    DefaultItem items[4];
} DefaultItemTable;

typedef struct {
    u8 pad_00[0x10];
    int movieId;
} MovieConfig;

extern DefaultItemTable data_ov030_020bcf6c;
extern MovieConfig gMarkerReset;
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern int func_ov001_02064784(void);

void InitMovieSelectionItems(void)
{
    int i = 0;
    SelectionList *list = &GetOverlaySelectionRecord(0)->list;
    DefaultItemTable defaults = data_ov030_020bcf6c;

    list->count = 0;
    for (; i < 4; i++) {
        list->items[i].kind = defaults.items[i].kind;
        list->items[i].level = defaults.items[i].level;
        list->count++;
    }
    list->selection = -1;
    gMarkerReset.movieId = -1;
    if (func_ov001_02064784() == 1) {
        gMarkerReset.movieId = 0x19c;
        return;
    }
    if (func_ov001_02064784() == 6) {
        gMarkerReset.movieId = 0x1a4;
    }
}

