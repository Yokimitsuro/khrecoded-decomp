#include "nitro/types.h"

typedef union GaugeOffset {
    u32 raw;
    struct {
        s16 x;
        s16 y;
    } pos;
} GaugeOffset;

typedef struct OptionMenu OptionMenu;
typedef void (*OptionApplyFunc)(OptionMenu *menu, u8 *target, int apply);

struct OptionMenu {
    u8 pad_00000[0x13e7d];
    u8 choice;
    u8 pad_13e7e[0x13e8c - 0x13e7e];
    u8 *targets[5];
    int page;
    OptionApplyFunc onApply;
    u8 pad_13ea8[0x13eb8 - 0x13ea8];
    GaugeOffset currentOffset;
    GaugeOffset savedOffset;
};

typedef struct SoundFlags {
    u32 mode : 2;
    u32 rest : 30;
} SoundFlags;

typedef struct SaveData {
    u8 pad_0000[0x2878];
    SoundFlags sound;
    u8 pad_287c[0x2c62 - 0x287c];
    u8 soundOption;
    u8 option5;
    u8 option4;
    u8 option2;
    u8 option3;
} SaveData;

extern SaveData *data_0205fe0c;

extern void SetGlobalPackedBit(int bitIndex);
extern void func_ov075_020c5d30(OptionMenu *menu, int a, int b, int c);
extern GaugeOffset GetSlotCellOffset(u8 value);
extern void ResetMatrixDescription(OptionMenu *menu);

void CommitOptionChoice(OptionMenu *menu, BOOL confirmed)
{
    if (confirmed) {
        int bitIndex = -1;
        BOOL changed = FALSE;

        switch (menu->page) {
        case 1:
            if (menu->choice != data_0205fe0c->soundOption) {
                changed = TRUE;
            }
            data_0205fe0c->sound.mode = data_0205fe0c->soundOption;
            bitIndex = 0xbeb;
            break;
        case 5:
            if (menu->choice != data_0205fe0c->option5) {
                changed = TRUE;
            }
            bitIndex = 0xbec;
            break;
        case 4:
            if (menu->choice != data_0205fe0c->option4) {
                changed = TRUE;
            }
            bitIndex = 0xbed;
            break;
        case 2:
            if (menu->choice != data_0205fe0c->option2) {
                changed = TRUE;
            }
            bitIndex = 0xbee;
            break;
        case 3:
            if (menu->choice != data_0205fe0c->option3) {
                changed = TRUE;
            }
            bitIndex = 0xbef;
            break;
        }
        if (changed) {
            SetGlobalPackedBit(bitIndex);
        }
        func_ov075_020c5d30(menu, -1, -1, 0);
    } else {
        u8 *target = menu->targets[menu->page - 1];

        *target = menu->choice;
        if (menu->page == 3) {
            GaugeOffset offset = GetSlotCellOffset(*target);

            menu->savedOffset = offset;
            menu->currentOffset = offset;
        }
        menu->onApply(menu, menu->targets[menu->page - 1], 1);
    }
    ResetMatrixDescription(menu);
}
