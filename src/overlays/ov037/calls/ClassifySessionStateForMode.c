#include "nitro/types.h"

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern s32 func_ov001_020644c0(void);
extern BOOL func_ov001_020645c8(u32 value);
extern signed char func_ov001_02068084(void);

int ClassifySessionStateForMode(void)
{
    s32 state;

    if (ReadSessionPackedBits(0x1a00, 2) == 0 || ReadSessionPackedBits(0x1a00, 2) == 1) {
        state = func_ov001_020644c0();
        switch (func_ov001_02068084()) {
        case 0:
            return state == 6;
        case 1:
            switch (state) {
            case 0x1e:
            case 0x1f:
            case 0x20:
            case 0x21:
                return 1;
            case 0x22:
                return 2;
            default:
                return 0;
            }
        case 2:
            switch (state) {
            case 0x1e:
            case 0x1f:
            case 0x20:
                return 1;
            }
            return 0;
        case 3:
            switch (state) {
            case 5:
            case 0xf:
            case 0x19:
            case 0x1e:
                return 1;
            }
            return 0;
        case 4:
            switch (state) {
            case 0x1e:
                return 1;
            }
            return 0;
        case 5:
            switch (state) {
            case 0x10:
                return 1;
            }
            return 0;
        case 6:
            switch (state) {
            case 0x17:
                return 1;
            case 0x18:
                return 2;
            case 0x63:
                return 3;
            case 0x1a:
                return func_ov001_020645c8(0x371e) ? 5 : 4;
            }
            return 0;
        case 7:
            if (func_ov001_020645c8(0x370c) || func_ov001_020645c8(0x370d)) {
                return -1;
            }
            if (state == 6) {
                return -1;
            }
            return func_ov001_020644c0() == 9;
        }
    }
    return -1;
}





