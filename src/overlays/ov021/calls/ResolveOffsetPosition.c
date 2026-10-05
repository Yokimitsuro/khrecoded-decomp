#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct {
    void *actor;
    u32 pad_04;
    void *target;
} StageGlobals;

extern StageGlobals data_ov021_020b56c4;
extern VecFx32 data_0205344c;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *tagged);
extern void ResolveVectorOperand(ScriptContext *context, TaggedValue *operand, VecFx32 *out);
extern s32 func_ov021_020b4ac4(ScriptContext *context, s32 offset);
extern u16 FindActorResourceIndexByName(void *actor, s32 name);
extern void GetNodePosition(void *owner, u32 nodeId, VecFx32 *out);
extern int _s32_div_f(int range, int value);
extern void func_ov021_020b0470(fx32 angle, fx32 length, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

u16 ResolveOffsetPosition(ScriptContext *context, int flags, TaggedValue *operands, VecFx32 *out, s32 *outName) {
    VecFx32 offset;
    if (flags & 1) {
        *out = context->position;
    } else if (flags & 2) {
        ResolveVectorOperand(context, operands, out);
    } else {
        void *target = data_ov021_020b56c4.target;
        if (target != NULL) {
            s32 name = func_ov021_020b4ac4(context, operands->value);
            GetNodePosition(target, FindActorResourceIndexByName(target, name), out);
            *outName = name;
        }
    }
    offset = data_0205344c;
    if (flags & 0x20) {
        ResolveVectorOperand(context, operands + 3, &offset);
    } else if (flags & 0x40) {
        TaggedValue *length = ResolveTaggedValueRef(context, operands + 3);
        TaggedValue *angle = ResolveTaggedValueRef(context, operands + 4);
        TaggedValue *scale = ResolveTaggedValueRef(context, operands + 5);
        int turn = _s32_div_f(0xffff, angle->value);
        func_ov021_020b0470(turn * scale->value, TaggedValueToFixed(length), &offset);
    }
    VEC_Add(out, &offset, out);
    return flags;
}
