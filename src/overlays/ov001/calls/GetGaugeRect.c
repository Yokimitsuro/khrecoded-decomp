#include "nitro/types.h"

typedef struct {
    u32 current;
    u32 limit;
    u8 pad_08[0x20];
    u16 flags;
    u16 count;
} GaugeEntry;

typedef struct {
    u8 pad_000[0x68];
    s32 unk_68;
    u8 pad_06C[0x5C];
    s32 unk_C8;
    u8 pad_0CC[0x30];
    s32 state;
    u8 pad_100[8];
    s32 unk_108;
} FieldMenu;

extern u32 _u32_div_f(u32 dividend, u32 divisor);

void GetGaugeRect(FieldMenu *menu, GaugeEntry *entry, s32 index, u32 value, u16 *outLeft,
                           u16 *outRight, u16 *outTop, u16 *outBottom, u16 *outFill)
{
    s32 left;
    s32 bottom;
    s32 top;
    s32 fill;
    s32 right;
    BOOL active;
    BOOL flagged;

    switch (menu->state) {
    case 0:
    case 1:
        left = ((index == 0 && (entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) ? 8 : 0) + 2;
        top = (index * 2 + 18) * 8 + 1;
        bottom = top + 13;
        break;
    case 2:
        left = 2;
        switch (index) {
        case -1:
            top = (index * 2 + 18) * 8;
            if (menu->unk_C8 < 3) {
                top++;
                bottom = top + 13;
            } else {
                bottom = top + 6;
            }
            break;
        case 0:
            if (menu->unk_C8 < 3) {
                top = (index * 2 + 18) * 8;
                bottom = top + 6;
            } else {
                top = (index * 2 + 17) * 8 + 1;
                bottom = top + 13;
            }
            break;
        case 1:
            top = (index * 2 + 17) * 8 + 1;
            bottom = top + 13;
            break;
        }
        break;
    case 3:
        left = 2;
        top = ((index == -1 && menu->unk_C8 < 3) ? index * 2 + 18 : index * 2 + 19) * 8 + 1;
        if (index == 1) {
            bottom = top + 7;
        } else {
            bottom = top + 13;
        }
        break;
    case 4:
        switch (index) {
        case -1:
            if (menu->unk_C8 < 3) {
                left = 2;
            } else {
                left = (menu->unk_108 * 3 - 8) * 8 + 2;
                if (left > 2) {
                    left = 2;
                }
            }
            break;
        case 0:
            if (menu->unk_C8 < 3) {
                left = (menu->unk_108 * 3 - 8) * 8 + 2;
                if ((entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
                    if (left > 10) {
                        left = 10;
                    }
                } else {
                    if (left > 2) {
                        left = 2;
                    }
                }
            } else {
                active = FALSE;
                flagged = FALSE;
                if ((entry->flags & 1) && (entry->flags & 4)) {
                    flagged = TRUE;
                }
                if (flagged && menu->unk_68 != 10) {
                    active = TRUE;
                }
                left = active ? 10 : 2;
            }
            break;
        case 1:
            left = 2;
            break;
        }
        top = (index * 2 + 18) * 8 + 1;
        bottom = top + 13;
        break;
    case 5:
        switch (index) {
        case -1:
            left = 2;
            break;
        case 0:
            active = FALSE;
            flagged = FALSE;
            if ((entry->flags & 1) && (entry->flags & 4)) {
                flagged = TRUE;
            }
            if (flagged && menu->unk_68 != 10) {
                active = TRUE;
            }
            left = active ? 10 : 2;
            break;
        case 1:
            left = (menu->unk_108 * 3 - 8) * 8 + 2;
            if (left > 2) {
                left = 2;
            }
            break;
        }
        top = (index * 2 + 18) * 8 + 1;
        bottom = top + 13;
        break;
    }

    if (entry->limit == 0) {
        fill = 0;
    } else {
        fill = left + _u32_div_f(value * 67, entry->limit);
    }
    if (fill < 0) {
        fill = 0;
    }
    right = left + 67;
    if (right < 0) {
        right = 0;
    }
    if (left < 0) {
        left = 0;
    }
    *outLeft = left;
    *outRight = right;
    *outTop = top;
    *outBottom = bottom;
    *outFill = fill;
}
