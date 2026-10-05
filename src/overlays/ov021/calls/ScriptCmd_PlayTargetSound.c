#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    void *actor;
    u32 pad_04;
    void *target;
} StageGlobals;

extern StageGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(void *context, TaggedValue *value);
extern int TaggedValueToInt(TaggedValue *tagged);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern void PlayActorSound(void *actor, u16 bank, u16 soundId, u32 flags, u16 volume);

int ScriptCmd_PlayTargetSound(void *context, TaggedValue *operands)
{
    TaggedValue *bank;
    TaggedValue *sound;
    TaggedValue *loop;
    TaggedValue *sessionOnly;
    void *target;
    int sessionFlag;
    u32 flags;
    int mode;

    bank = ResolveTaggedValueRef(context, operands);
    sound = ResolveTaggedValueRef(context, operands + 1);
    loop = ResolveTaggedValueRef(context, operands + 2);
    sessionOnly = ResolveTaggedValueRef(context, operands + 3);
    target = data_ov021_020b56c4.target;
    sessionFlag = 0;
    flags = 0;
    if (target == NULL) {
        return 0;
    }
    if (func_ov001_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    if (mode == 7) {
        sessionFlag = TaggedValueToInt(sessionOnly);
    }
    if (TaggedValueToInt(loop) != 0) {
        flags |= 1;
    }
    if (sessionFlag != 0) {
        flags |= 4;
    }
    PlayActorSound(target, TaggedValueToInt(bank), TaggedValueToInt(sound), flags, 0);
    return 0;
}
