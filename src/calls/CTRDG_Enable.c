#include "nitro/types.h"
#include "nitro/ctrdg.h"

extern struct {
    BOOL enableFlag;
    CTRDGWork work;
} data_0205a2a0;

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern BOOL CTRDGi_HasValidModuleInfo(void);
extern u32 OS_SetDPermissionsForProtectionRegion(u32 mask, u32 access);
extern void DC_FlushAll(void);
extern void DC_WaitWriteBufferEmpty(void);
extern void OS_EnableICacheForProtectionRegion(u32 regions);
extern void OS_DisableICacheForProtectionRegion(u32 regions);
extern void OS_EnableDCacheForProtectionRegion(u32 regions);
extern void OS_DisableDCacheForProtectionRegion(u32 regions);
extern void OS_EnableWriteBufferForProtectionRegion(u32 regions);
extern void OS_DisableWriteBufferForProtectionRegion(u32 regions);

void CTRDG_Enable(BOOL enable) {
    int state = OS_DisableInterrupts();

    data_0205a2a0.enableFlag = enable;

    if (CTRDGi_HasValidModuleInfo()) {
        u32 access = enable ? (1 << 12) : (5 << 12);
        OS_SetDPermissionsForProtectionRegion(0xf << 12, access);
        if (enable) {
            DC_FlushAll();
            DC_WaitWriteBufferEmpty();
            OS_DisableICacheForProtectionRegion(8);
            OS_DisableDCacheForProtectionRegion(8);
            OS_DisableWriteBufferForProtectionRegion(8);
        } else {
            OS_EnableICacheForProtectionRegion(8);
            OS_EnableDCacheForProtectionRegion(8);
            OS_EnableWriteBufferForProtectionRegion(8);
        }
    }

    OS_RestoreInterrupts(state);
}
