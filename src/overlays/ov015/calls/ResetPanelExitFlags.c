#include "nitro/types.h"

extern void func_ov015_0206eb2c(void);
extern void func_ov015_0206eba4(void);
extern u8 *data_ov015_0207e960;

void ResetPanelExitFlags(void) {
    func_ov015_0206eb2c();
    func_ov015_0206eba4();
    *(u32 *)(data_ov015_0207e960 + 0xe4) = 0;
    data_ov015_0207e960[0xba] = 0;
}
