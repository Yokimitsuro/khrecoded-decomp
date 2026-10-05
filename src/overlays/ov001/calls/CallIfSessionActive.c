#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void func_ov001_0209cb08(u16 id);

void CallIfSessionActive(int id)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209cb08(id);
    }
}
