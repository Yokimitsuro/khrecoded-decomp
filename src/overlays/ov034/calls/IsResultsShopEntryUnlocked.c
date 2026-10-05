#include "nitro/types.h"

typedef struct ResultsParams {
    u8 pad_00[0x24];
    u8 unlockedRank;
    u8 maxRank;
} ResultsParams;

typedef struct ResultsWork {
    u8 pad_0000[0x6d68];
    int shopBase;
} ResultsWork;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct ShopEntry {
    u8 pad_00[9];
    s8 requiredRank;
    u8 pad_0a[2];
} ShopEntry;

extern ResultsScreen data_ov034_020c0fa0;
extern ShopEntry data_ov034_020bed6c[];
extern void func_ov034_020be438(int index);
extern int ClassifyResultsShopEntry(int index);

BOOL IsResultsShopEntryUnlocked(int index)
{
    ShopEntry *entry;
    int rank;

    func_ov034_020be438(index);
    entry = &data_ov034_020bed6c[data_ov034_020c0fa0.work->shopBase + index];
    if (ClassifyResultsShopEntry(index) != 0 ||
        ((rank = entry->requiredRank) >= 0 && rank <= data_ov034_020c0fa0.params->unlockedRank) ||
        (rank < 0 && data_ov034_020c0fa0.params->unlockedRank == data_ov034_020c0fa0.params->maxRank)) {
        return TRUE;
    }
    return FALSE;
}
