#include "nitro/types.h"

extern u32 data_ov053_020d2c40;
extern u32 func_ov052_020ccc80();
extern u32 func_ov001_02063a38();
extern void func_ov040_020be00c();
extern u32 func_ov001_0206e31c();
extern u32 func_ov010_020a1828();

void ShutdownOverlay053(void)
{
    s32 result;

    if (data_ov053_020d2c40 != 0) {
        func_ov052_020ccc80();
        result = func_ov001_02063a38();
        if (result == 6) {
            func_ov040_020be00c();
        }
        result = func_ov001_0206e31c();
        if (result != 0) {
            func_ov010_020a1828();
        }
        data_ov053_020d2c40 = 0;
    }
}
