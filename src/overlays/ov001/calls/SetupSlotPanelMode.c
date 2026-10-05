#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x27f1];
    u8 lowBits : 4;
    u8 slotsReady : 1;
} FieldState;

extern FieldState *data_ov001_020a0480;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern u32 PopCount32(u32 value);
extern BOOL InitSlotLayout(int first, int second);
extern BOOL InitSlotLayoutCompact(u32 mode);
extern void func_ov001_020645dc(u32 flag);
extern void ClearSessionPackedBit(u32 flag);
extern int func_ov001_0207d3ac(int value);

void SetupSlotPanelMode(int mode, int enable) {
    FieldState *field = data_ov001_020a0480;

    switch (mode) {
    case 0:
        if (enable) {
            if (!field->slotsReady) {
                InitSlotLayout(0x10, PopCount32(ReadSessionPackedBits(0x3700, 0x10)));
                field->slotsReady = 1;
            }
            func_ov001_020645dc(0x3716);
        } else {
            ClearSessionPackedBit(0x3716);
        }
        break;
    case 1:
        if (enable) {
            if (!field->slotsReady) {
                InitSlotLayoutCompact(ReadSessionPackedBits(0x3700, 0x10));
                field->slotsReady = 1;
            }
            func_ov001_020645dc(0x3714);
        } else {
            ClearSessionPackedBit(0x3714);
        }
        break;
    case 2:
        if (enable && !field->slotsReady) {
            field->slotsReady = 1;
        }
        break;
    }
    func_ov001_0207d3ac(enable);
}
