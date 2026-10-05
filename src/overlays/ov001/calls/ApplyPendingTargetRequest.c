#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RecordInfo {
    u16 itemId;
    u16 flagsLow : 1;
    u16 packedTarget : 1;
    u16 flagsHigh : 14;
    u8 pad_04[0x20];
} RecordInfo;

typedef struct TargetRequest {
    s32 kind;
    union {
        u32 id;
        struct {
            s16 recordId;
            s16 slot;
        };
    };
} TargetRequest;

typedef struct TargetState {
    u32 flags;
    TargetRequest request;
    u8 pad_0c[0xc0];
    u8 cursor[0x148];
    fx32 screen[2];
} TargetState;

extern TargetState *data_ov001_020a04a4;
extern BOOL func_ov001_02087988(u16 recordId, RecordInfo *info);
extern VecFx32 *func_ov001_0206c284(void);
extern void SelectCursorTarget(void *cursor, u32 target);
extern void func_ov001_0206bfec(void *cursor, int id);
extern void func_ov001_0206c038(void *cursor);
extern int ProjectWorldToScreenFx(const VecFx32 *world, fx32 *screen);

void ApplyPendingTargetRequest(void)
{
    TargetState *state = data_ov001_020a04a4;
    TargetRequest *request;
    VecFx32 *target = NULL;
    RecordInfo info;

    request = &state->request;
    if (request->kind == 0) {
        return;
    }
    switch (request->kind) {
    case 1:
        if (func_ov001_02087988(request->recordId, &info)) {
            target = func_ov001_0206c284();
            if (!info.packedTarget) {
                func_ov001_0206c038(state->cursor);
            } else {
                func_ov001_0206bfec(state->cursor, (request->recordId << 15) | request->slot);
            }
        }
        break;
    case 2:
        target = func_ov001_0206c284();
        if (target != NULL) {
            SelectCursorTarget(state->cursor, request->id);
        }
        break;
    case 3:
        target = func_ov001_0206c284();
        if (target != NULL) {
            func_ov001_0206bfec(state->cursor, request->id);
        }
        break;
    case 4:
        target = func_ov001_0206c284();
        func_ov001_0206c038(state->cursor);
        break;
    }
    if (target == NULL) {
        return;
    }
    if (ProjectWorldToScreenFx(target, state->screen) != -1) {
        state->flags |= 0x10;
    }
}
