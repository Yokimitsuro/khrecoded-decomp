#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[0x80];
    u16 heading;
} ActorNode;

typedef struct ChannelBuffer {
    u8 pad_00[0x44];
    s32 rotationX;
    s32 rotationY;
    u8 pad_4c[0x98 - 0x4c];
    s32 state;
} ChannelBuffer;

typedef struct CollisionEntry {
    u8 pad_00[0x8];
    VecFx32 position;
} CollisionEntry;

typedef struct ScriptContext ScriptContext;

extern const VecFx32 data_0205344c;
extern ScriptOperand *ScriptVm_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern CollisionEntry *FindWorldCollisionEntry(void *name);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern ChannelBuffer *ActorChannel_SelectBuffer(void);
extern void ActorChannel_SetStateFields(u32 state, u32 value);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void SetFieldCameraTarget(int actorId, int mode, fx32 speed, int roll, VecFx32 *position, VecFx32 *rotation);

int ScriptCmd_StartChannelTransform(ScriptContext *context, ScriptOperand *args)
{
    VecFx32 position = data_0205344c;
    VecFx32 rotation = data_0205344c;
    int roll = 0;
    fx32 speed;
    int mode;
    int actorId;
    ScriptOperand *operand;
    int angle;
    CollisionEntry *entry;

    speed = ScriptVm_ReadOperandFx32(context, &args[2]);
    mode = ScriptVm_ReadOperandInt(context, &args[1]);
    actorId = 0;
    position.x = ScriptVm_ReadOperandFx32(context, &args[3]);
    position.y = ScriptVm_ReadOperandFx32(context, &args[4]);
    position.z = ScriptVm_ReadOperandFx32(context, &args[5]);

    operand = ScriptVm_ResolveOperand(context, &args[0]);
    switch (operand->type) {
    case 1:
        if (operand->value != -1) {
            actorId = ScriptCmd_ReturnValue(context, operand->value);
        } else {
            actorId = -1;
        }
        break;
    case 2:
        entry = FindWorldCollisionEntry(ByteCode_ResolveOperand(context, operand));
        actorId = -1;
        VEC_Add(&position, &entry->position, &position);
        break;
    }

    if (ActorChannel_SelectBuffer()->state == 8) {
        rotation.x = ActorRegistry_GetEntityByIndex(actorId)->heading;
        ActorChannel_SetStateFields(3, 0);
    } else {
        operand = ScriptVm_ResolveOperand(context, &args[6]);
        if (operand->type != 0) {
            rotation.x = ScriptVm_ReadOperandInt(context, operand) * 0xb6;
        } else {
            rotation.x = ActorChannel_SelectBuffer()->rotationX;
        }
    }

    operand = ScriptVm_ResolveOperand(context, &args[7]);
    if (operand->type == 1) {
        angle = ScriptVm_ReadOperandInt(context, operand);
        if (angle > 360) {
            angle = -(angle - 360);
        }
        rotation.y = angle * 0xb6;
    } else {
        rotation.y = ActorChannel_SelectBuffer()->rotationY;
    }

    operand = ScriptVm_ResolveOperand(context, &args[8]);
    if (operand->type == 1) {
        rotation.z = ScriptVm_ReadOperandInt(context, operand) * 0xb6;
    }

    operand = ScriptVm_ResolveOperand(context, &args[9]);
    if (operand->type == 1) {
        roll = ScriptVm_ReadOperandInt(context, operand) * 0xb6;
    }

    SetFieldCameraTarget(actorId, mode, speed, roll, &position, &rotation);
    return 1;
}
