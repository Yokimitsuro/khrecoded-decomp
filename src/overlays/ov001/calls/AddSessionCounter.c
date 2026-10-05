#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Session {
    u8 pad_0000[0x2938];
    s32 counters[29];
} Session;

extern Session *data_ov001_020a0480;
extern s32 data_ov001_0209d940[];
extern BOOL func_ov001_02088100(VecFx32 *out);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void SpawnRewardOrbs(u16 *amounts, void *position, int popupFlags);
extern void func_02027390(int messageId, int category, int amount, int limit);
extern void ClearSessionPackedBit(u32 eventId);
extern int func_ov001_020644b0(void);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void AddSessionCounter(int index, int amount) {
    int popupFlags;
    s32 *counters = data_ov001_020a0480->counters;
    int value;
    counters[index] += amount;
    if (amount > 0) {
        value = data_ov001_0209d940[index];
        if (value < counters[index]) {
            counters[index] = value;
        }
    } else if (counters[index] < 0) {
        counters[index] = 0;
    }
    switch (index) {
    case 1:
        if (amount < 0) {
            VecFx32 target;
            u16 amounts[6] = {0};
            popupFlags = 4;
            amounts[4] = -amount;
            if (func_ov001_02088100(&target)) {
                popupFlags = 5;
            }
            SpawnRewardOrbs(amounts, func_ov001_0206dc4c(0), popupFlags);
            return;
        }
        func_02027390(0xb37, 0x11, amount, 99999);
        return;
    case 12:
        ClearSessionPackedBit(0x35ca);
        return;
    case 28:
        if (func_ov001_020644b0() == 100) {
            value = ReadSessionPackedBits(0x3700, 7);
            value += amount;
            if (value >= 99) {
                value = 99;
            }
            WriteSessionPackedBits(0x3700, 7, value);
        }
        func_02027390(0xaf3, 0x11, amount, 99999);
        return;
    }
}
