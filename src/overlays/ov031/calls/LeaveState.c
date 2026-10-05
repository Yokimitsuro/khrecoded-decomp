#include "nitro/types.h"

extern void func_02035de4(void);
extern void func_ov001_02067d48(void);
extern void func_ov001_0206daa8(void);
extern void func_ov001_020876d4(void);
extern void func_ov021_020af528(u32 a);
extern void func_ov031_020bb2f4(void);

void LeaveState(void)
{
    func_ov021_020af528(1);
    func_ov001_02067d48();
    func_ov031_020bb2f4();
    func_ov001_0206daa8();
    func_02035de4();
    func_ov001_020876d4();
}
