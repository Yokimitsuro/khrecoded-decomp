#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LockFlags {
    u8 blocked;
    u8 locked;
} LockFlags;

typedef struct ContactState {
    u8 pad_000[0x194];
    LockFlags lock;
} ContactState;

typedef struct ContactOwner {
    ContactState **state;
    s32 isStatic;
} ContactOwner;

typedef struct Contact {
    ContactOwner *owner;
    s32 type;
} Contact;

typedef struct FieldManager {
    u8 pad_00[0x64];
    s16 effectBank;
} FieldManager;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldManager *manager;
    u8 pad_08[0x30];
    VecFx32 position;
    u8 pad_44[0xe];
    u8 kind;
    u8 pad_53;
    s8 cooldown;
} FieldObject;

typedef struct PushParams {
    u8 pad_00[4];
    u16 strength;
} PushParams;

typedef struct PartyEntry {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x1d4 - 0xc8];
    PushParams *pushParams;
} PartyEntry;

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

extern void SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern PartyEntry *func_ov001_0206db5c(int index);
extern BOOL IsMovingAgainstDirection(FieldObject *object, int entryIndex, VecFx32 *direction);
extern BOOL func_ov001_0208655c(FieldObject *object, int arg, VecFx32 *direction, fx32 threshold);
extern void func_ov021_020a8ad4(EffectRequest *request);
extern void func_ov021_020a8cc0(EffectRequest *request, int bank);

void FieldObject_HandlePushContact(void *arg0, void *arg1, VecFx32 *direction, Contact *contact,
                                           void *userData)
{
    FieldObject *object = userData;
    PartyEntry *entry;
    fx32 threshold;
    EffectRequest effect;
    LockFlags *lock;
    VecFx32 *origin;
    u8 cleared;

    if (object->kind != 3 || object->cooldown != 0) {
        return;
    }
    if (contact == NULL || contact->type != 2 || contact->owner->isStatic != 0) {
        return;
    }
    lock = &(*contact->owner->state)->lock;
    if (lock->blocked != 0 || lock->locked != 0) {
        return;
    }
    if (!IsMovingAgainstDirection(object, lock->locked, direction)) {
        return;
    }
    cleared = 0;
    SpawnSoundSlot(0, 0x36, &object->position, 0);
    entry = func_ov001_0206db5c(0);
    origin = &entry->position;
    threshold = (entry->pushParams->strength << 12) / 10;
    if (func_ov001_0208655c(object, 0, direction, threshold)) {
        func_ov021_020a8ad4(&effect);
        effect.unk_25 = cleared;
        effect.position = *origin;
        effect.unk_00 = cleared;
        effect.position.y += 0xc00;
        effect.unk_24 = cleared;
        func_ov021_020a8cc0(&effect, object->manager->effectBank);
    }
    object->cooldown = 0x24;
}
