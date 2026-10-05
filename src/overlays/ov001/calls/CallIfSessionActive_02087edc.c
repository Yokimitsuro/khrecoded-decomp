#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void func_ov001_0209c6f0(u16 id, int arg, int extra);

void CallIfSessionActive_02087edc(int id, int arg, int extra)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209c6f0(id, arg, extra);
    }
}
