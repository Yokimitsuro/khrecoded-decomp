#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x214];
    u32 lowFlags : 13;
    u32 menuLocked : 1;
} Session;

typedef struct SaveData {
    u8 pad_0000[0x28d5];
    s8 areaId;
} SaveData;

typedef struct RewardItem {
    u8 pad_00[4];
    int owned;
    u8 pad_08[0x20 - 8];
    int type;
} RewardItem;

typedef struct RewardEntry {
    u16 id;
    u8 pad_02[6];
    RewardItem *item;
} RewardEntry;

extern Session *data_ov001_020a0480;
extern SaveData *data_0205fe0c;

extern signed char func_ov001_02068084(void);
extern BOOL func_ov075_020cec24(void);
extern BOOL IsPartyLevelSufficient(void);
extern BOOL func_ov075_020cecf0(void);
extern BOOL func_ov075_020ced2c(void);

static inline BOOL IsOutsideStoryArea(void)
{
    BOOL outside = FALSE;

    if (data_0205fe0c->areaId != 0x1d && data_0205fe0c->areaId != 0x1e) {
        outside = TRUE;
    }
    return outside;
}

static inline BOOL IsFieldMode(void)
{
    BOOL field = FALSE;

    if (func_ov001_02068084() == 3 && IsOutsideStoryArea()) {
        field = TRUE;
    }
    return field;
}

BOOL IsRewardEntryLocked(RewardEntry *entry)
{
    BOOL locked = TRUE;
    BOOL sufficient;

    if (data_ov001_020a0480->menuLocked) {
        return FALSE;
    }
    if (entry->item->owned != 0 || entry->id == 0) {
        locked = FALSE;
    } else {
        switch (entry->item->type) {
        case 0xb7:
        case 0xb8:
            if (func_ov075_020cec24()) {
                locked = FALSE;
            }
            break;
        case 0xb9:
        case 0xba:
            if (IsFieldMode()) {
                locked = FALSE;
                break;
            }
            if (func_ov075_020ced2c()) {
                locked = FALSE;
                break;
            }
            sufficient = IsPartyLevelSufficient();
            locked = TRUE;
            if (sufficient) {
                locked = FALSE;
            }
            break;
        case 0xbd:
            if (IsFieldMode()) {
                locked = FALSE;
            }
            if (IsPartyLevelSufficient() && func_ov075_020cec24() && func_ov075_020cecf0()) {
                locked = FALSE;
            }
            break;
        case 0xbc:
            if (IsFieldMode()) {
                locked = FALSE;
            }
            if (func_ov075_020cec24() && func_ov075_020cecf0()) {
                locked = FALSE;
            }
            break;
        case 0xbb:
            if (IsFieldMode()) {
                locked = FALSE;
            }
            if (func_ov075_020cecf0()) {
                locked = FALSE;
            }
            break;
        }
    }
    return locked;
}
