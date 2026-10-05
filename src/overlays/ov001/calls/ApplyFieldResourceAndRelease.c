#include "nitro/types.h"

typedef struct FieldManager FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern u32 func_ov027_020ba1f8(void *resource);
extern void func_ov001_0206efac(FieldManager *manager, u32 resourceManager);
extern void func_ov027_020ba200(void *resource, BOOL freeData);

void ApplyFieldResourceAndRelease(void *resource)
{
    FieldManager *manager = data_ov001_020a04c4.manager;

    func_ov001_0206efac(manager, func_ov027_020ba1f8(resource));
    func_ov027_020ba200(resource, TRUE);
}
