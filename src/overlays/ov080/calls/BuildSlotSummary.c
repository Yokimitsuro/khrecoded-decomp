#include "nitro/types.h"

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    u8 pad_00[0x28c4];
    u32 flags;
    u32 playTime;
    u8 pad_28cc[4];
    u32 money;
} SaveFields;

typedef struct {
    s32 status : 8;
    s32 frameIndex : 8;
    u32 statusHigh : 16;
    u8 pad_04[0x20];
    char levelText[8];
    char moneyText[14];
    char playTimeText[20];
    char titleText[0x82];
    SaveData saveData;
} SaveSlot;

typedef struct {
    u8 pad_00[0xa920];
    u32 unlockedA;
    u32 unlockedB;
} SaveSelectScreen;

typedef struct {
    u8 pad_00;
    u8 level;
} SelectionRecord;

extern SaveData *data_0205fe0c;
extern const char data_ov080_020c5dfc[];
extern const char data_ov080_020c5e04[];
extern int *AcquireMapLayout(BOOL reload, BOOL discard);
extern void RebuildRecordCounters(void);
extern SelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats(SaveData *state, void *out, BOOL recompute, int scaleParam);
extern void func_ov073_020c1ed4(SaveData *saveData, void *options);
extern void func_02050a58(void);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);
extern void func_ov039_020be66c(char *dst, u32 playTime);
extern void func_020273e8(void);
extern const char *func_ov039_020bcb40(SaveData *save);

void BuildSlotSummary(SaveSelectScreen *screen, SaveSlot *slot)
{
    SaveFields *save = (SaveFields *)data_0205fe0c;
    BOOL flag = TRUE;
    int status;

    AcquireMapLayout(TRUE, FALSE);
    RebuildRecordCounters();
    ComputePlayerStats(data_0205fe0c, GetOverlaySelectionRecord(0), TRUE, 0);
    func_ov073_020c1ed4(data_0205fe0c, NULL);
    func_02050a58();
    if (!IsGlobalPackedBitSet(0xf4c)) {
        flag = FALSE;
    }
    screen->unlockedA |= (u8)flag;
    screen->unlockedB |= (u8)(IsGlobalPackedBitSet(0xf4d) ? 1 : 0);
    status = IsGlobalPackedBitSet(0xbea) ? 3 : 2;
    slot->status = status;
    slot->frameIndex = ((save->flags & 0xc0000000) >> 30) + 1;
    OS_SNPrintf_0202e094(slot->levelText, 4, data_ov080_020c5dfc, GetOverlaySelectionRecord(0)->level + 1);
    OS_SNPrintf_0202e094(slot->moneyText, 7, data_ov080_020c5dfc, save->money);
    func_ov039_020be66c(slot->playTimeText, save->playTime);
    func_020273e8();
    OS_SNPrintf_0202e094(slot->titleText, 0x40, data_ov080_020c5e04, func_ov039_020bcb40((SaveData *)save));
    slot->saveData = *data_0205fe0c;
}
