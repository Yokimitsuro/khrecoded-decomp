#include "nitro/types.h"

extern u32 data_ov035_020bc500;
extern void SetSoundListenersEnabled(int arg);
extern void func_ov001_0206a714(void);
extern void func_ov001_0206c6f4(void);
extern void func_ov001_02063c54(void);

/* Tears down the active movie context */
void TeardownMovieContext(void) {
    SetSoundListenersEnabled(0);
    if (*(int *)(data_ov035_020bc500 + 0x10) != -1) {
        func_ov001_0206a714();
        *(u32 *)(data_ov035_020bc500 + 0x10) = 0xffffffff;
    }
    func_ov001_0206c6f4();
    func_ov001_02063c54();
    data_ov035_020bc500 = 0;
}
