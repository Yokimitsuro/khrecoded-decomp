#include "nitro/types.h"
#include "nitro/fx_types.h"

struct FieldObject;

typedef struct TriggerLink {
    u8 kind;
    u8 pad_01;
    u16 arg;
} TriggerLink;

typedef struct ContactOwner {
    u8 pad_00[4];
    s32 isStatic;
} ContactOwner;

typedef struct Contact {
    ContactOwner *owner;
    s32 type;
} Contact;

typedef void (*ContactHandler)(void *context, struct FieldObject *object, u16 arg, void *arg0, void *arg1,
                               VecFx32 *direction, Contact *contact, void *userData, void *arg5,
                               void *arg6, void *arg7);

typedef struct FieldManager {
    u8 pad_000[0x170];
    s16 effectBank;
    u8 pad_172[0x2a];
    ContactHandler contactHandlers[1];
} FieldManager;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldManager *manager;
    u8 pad_08[0x30];
    VecFx32 position;
    u8 pad_44[0xc];
    s32 kind : 16;
    s32 subKind : 16;
    u8 pad_54[0xc];
    TriggerLink *trigger;
    u8 pad_64[8];
    s16 linkId;
    u8 pad_6E[2];
    VecFx32 normal;
    s32 pushDisabled;
} FieldObject;

typedef struct PushRequest {
    s32 type;
    VecFx32 velocity;
    VecFx32 origin;
    s32 power;
    s32 unk_20;
    u32 resultFlags;
    u8 pad_28[8];
    s32 unk_30;
    s32 unk_34;
} PushRequest;

typedef struct EffectRequest {
    u8 unk_00;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[2];
    s16 unk_28;
    s16 soundId;
} EffectRequest;

typedef BOOL (*PushHandler)(void *system, PushRequest *request);

typedef struct PushSystem {
    u8 pad_000[0x208];
    PushHandler push;
} PushSystem;

extern const VecFx32 data_0205344c;

extern FieldObject *func_ov001_02086384(FieldManager *manager);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern PushSystem *GetBoundedEntryField(int index);
extern void PlaySoundChecked(int bank, int soundId);
extern BOOL IsMovingAgainstDirection(FieldObject *object, int arg, VecFx32 *direction);
extern BOOL SendPushMessage(FieldObject *object, int arg, VecFx32 *direction, fx32 threshold);
extern void ResetAnimationTrackState(EffectRequest *request);
extern VecFx32 *func_ov001_0206dc60(void);
extern void func_ov021_020a8cc0(EffectRequest *request, int bank);

void FieldObject_HandleContact_020a33d8(void *arg0, void *arg1, VecFx32 *direction, Contact *contact, void *userData,
                         void *arg5, void *arg6, void *arg7)
{
    FieldObject *object;
    FieldManager *manager;
    TriggerLink *trigger;
    ContactHandler handler;
    VecFx32 normal;
    PushRequest request;
    EffectRequest effect;
    VecFx32 scaled;
    FieldObject *linked;
    fx32 dot;
    PushSystem *system;
    BOOL pushed;

    if (contact == NULL || contact->type != 2 || contact->owner->isStatic != 0) {
        return;
    }
    object = userData;
    manager = object->manager;
    if ((object->trigger != NULL && object->trigger->kind == 3) || object->linkId != -1) {
        if (object->linkId != -1) {
            linked = func_ov001_02086384(manager);
            if (linked->trigger == NULL || linked->trigger->kind != 3) {
                normal = data_0205344c;
            } else {
                normal = linked->normal;
            }
        } else {
            normal = object->normal;
        }
        if (object->pushDisabled == 0) {
            dot = VEC_DotProduct(&normal, direction);
            if (dot > 0x29) {
                request.power = dot * 7;
                request.type = 4;
                scaled = *direction;
                ScaleVecFx32InPlace(&scaled, dot);
                request.velocity = scaled;
                request.origin = object->position;
                pushed = FALSE;
                request.unk_20 = 0;
                request.unk_30 = 0;
                request.unk_34 = 0;
                system = GetBoundedEntryField(0);
                if (system->push != NULL) {
                    pushed = system->push(system, &request);
                }
                if (pushed && !(request.resultFlags & 1)) {
                    PlaySoundChecked(0, 0x36);
                }
            }
        }
    }
    if (object->kind == 3 && IsMovingAgainstDirection(object, 0, direction) &&
        SendPushMessage(object, 0, direction, 0x2000)) {
        ResetAnimationTrackState(&effect);
        effect.unk_00 = 0;
        effect.unk_25 = 0;
        effect.unk_24 = 0;
        effect.position = *func_ov001_0206dc60();
        effect.unk_28 = 0;
        effect.soundId = 0x36;
        func_ov021_020a8cc0(&effect, manager->effectBank);
    }
    trigger = object->trigger;
    if (trigger != NULL) {
        handler = manager->contactHandlers[trigger->kind];
        if (handler != NULL) {
            handler(&object->normal, object, trigger->arg, arg0, arg1, direction, contact, userData, arg5, arg6, arg7);
        }
    }
}
