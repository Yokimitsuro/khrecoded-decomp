#include "nitro/types.h"

extern int ShowMovieMessage3700(void);
extern int func_ov035_020bafb4(void);
extern void func_ov001_020645dc(int flagId);
extern int GetMovieCounterLimit(int kind);
extern void WriteSessionPackedBits(int id, int bits, int value);
extern int LoadMovieCounter(int mode);
extern void SetFieldSlotValue(int index, int value, u16 param, u16 extra);

void CommitSideResult(int side) {
    switch (side) {
    case 0:
        if (ShowMovieMessage3700() == 0) {
            func_ov001_020645dc(0x3700);
            WriteSessionPackedBits(0x3703, 0x10, GetMovieCounterLimit(1));
            SetFieldSlotValue(0, 1, LoadMovieCounter(0), LoadMovieCounter(0));
        }
        break;
    case 1:
        if (func_ov035_020bafb4() == 0) {
            func_ov001_020645dc(0x3701);
            WriteSessionPackedBits(0x3713, 0x10, GetMovieCounterLimit(2));
            SetFieldSlotValue(1, 0, LoadMovieCounter(0), LoadMovieCounter(0));
        }
        break;
    }
}
