#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 modelGroupResource;
} RegistryHead;

extern u32 Archive_LoadFile(u32 fileId, u32 param2, u32 param3, u32 param4);
extern int func_02035120(void *g, void *res);
extern RegistryHead *data_0206083c;

BOOL OpenActorModelGroupResource(u32 param1, u32 param2, u32 param3, u32 param4) {
    RegistryHead *registry = data_0206083c;
    u32 result = Archive_LoadFile(param2, 1, param3, param4);
    func_02035120(registry, (void *)result);
    registry->modelGroupResource = result;
    return TRUE;
}
