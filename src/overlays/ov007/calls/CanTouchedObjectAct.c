#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x194];
    u8 kind;
    u8 group;
    u8 index;
} ObjectExtension;

typedef struct {
    u8 pad_00[0x14];
    ObjectExtension *ext;
} TouchObject;

typedef struct {
    TouchObject *object;
    int kind;
} TouchContext;

typedef struct StageObject StageObject;

typedef struct {
    u8 pad_00[0x30];
    BOOL (*isBusy)(StageObject *object);
} StageObjectVtable;

struct StageObject {
    u32 unk_00;
    StageObjectVtable *vtable;
};

extern StageObject *func_ov001_0208724c(u32 group, u32 index);

BOOL CanTouchedObjectAct(TouchContext *ctx) {
    if (ctx->kind == 4 && ctx->object->ext->kind == 4) {
        StageObject *target = func_ov001_0208724c(ctx->object->ext->group, ctx->object->ext->index);

        if (target != NULL) {
            BOOL busy;

            if (target->vtable->isBusy == NULL) {
                busy = FALSE;
            } else {
                busy = target->vtable->isBusy(target);
            }
            if (busy) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
