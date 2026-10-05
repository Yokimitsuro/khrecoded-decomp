#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void func_ov001_0209c678(u16 id, int arg);

void CallIfSessionActive_02087ec0(int id, int arg)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209c678(id, arg);
    }
}
