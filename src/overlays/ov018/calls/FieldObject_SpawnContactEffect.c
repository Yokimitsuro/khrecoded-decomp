#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x470];
    s16 effectBank;
} FieldManager;

typedef struct {
    u8 pad_00[4];
    FieldManager *manager;
} FieldObject;

typedef struct {
    u8 pad_00[4];
    s32 isStatic;
} ContactOwner;

typedef struct {
    ContactOwner *owner;
    s32 type;
} Contact;

typedef struct {
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

extern BOOL func_ov001_0208655c(FieldObject *object, int arg, VecFx32 *direction, fx32 threshold);
extern void func_ov021_020a8ad4(EffectRequest *request);
extern VecFx32 *func_ov001_0206dc60(int index);
extern void func_ov021_020a8cc0(EffectRequest *request, int bank);

void FieldObject_SpawnContactEffect(void *arg0, void *arg1, VecFx32 *direction, Contact *contact, void *userData)
{
    FieldObject *object;
    EffectRequest effect;

    if (contact == NULL || contact->type != 2 || contact->owner->isStatic != 0) {
        return;
    }
    object = userData;
    if (func_ov001_0208655c(object, 0, direction, 0x2000)) {
        func_ov021_020a8ad4(&effect);
        effect.unk_00 = 0;
        effect.unk_25 = 0;
        effect.unk_24 = 0;
        effect.position = *func_ov001_0206dc60(0);
        effect.unk_28 = 0;
        effect.soundId = 0x36;
        func_ov021_020a8cc0(&effect, object->manager->effectBank);
    }
}

