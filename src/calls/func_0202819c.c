#include "nitro/types.h"

extern void SoundMgr_Update(void);
extern int func_0202852c(void);
extern void ResetPanelFieldB8AndNotify(void);

void func_0202819c(void) {
    SoundMgr_Update();
    if (func_0202852c() != 0) {
        ResetPanelFieldB8AndNotify();
    }
}
