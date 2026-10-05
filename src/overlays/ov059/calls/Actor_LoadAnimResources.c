#include "nitro/types.h"

typedef struct AnimSlot {
    u8 data[0x2c];
} AnimSlot;

typedef struct AnimHolder {
    u32 pad_00;
    u8 player[1];
} AnimHolder;

typedef struct Actor {
    u8 pad_0000[0x230];
    AnimHolder *anim;
    u8 pad_0234[0x76c - 0x234];
    AnimSlot animSlots[1];
    u8 pad_0798[0x908 - 0x798];
    int (*mapKindToSlot)(int kind);
    u8 pad_090c[0x930 - 0x90c];
    u8 playerIndex;
    u8 pad_0931[0x93c - 0x931];
    int state;
    u8 pad_0940[0x1828 - 0x940];
    u16 effectGroupId;
} Actor;

typedef struct NameList {
    const char *names[3];
} NameList;

typedef struct SlotList {
    int slots[3];
} SlotList;

typedef struct GroupDesc {
    const char *name;
    int count;
    int stride;
    BOOL fixed;
    int reserved;
} GroupDesc;

extern const NameList gBattleEffectPathParts;
extern const SlotList data_ov059_020cfe10;
extern const char sOv059_BaChFormatS_020cff2c[];
extern const char sOv059_BaChSoWd00_020cff38[];
extern const char *gSoundCategoryNames[];
extern void *OS_SPrintf(char *dst, const char *fmt, ...);
extern char *STD_ConcatenateString(char *dst, const char *src);
extern void AcquireSharedRecordState(AnimSlot *slot, const char *name, void *player, int context);
extern void ZeroBytes0x14(void *obj);
extern u16 func_ov021_020a89c8(GroupDesc *desc);
extern void LoadActorModel(Actor *actor);
extern int MapKindToSlotIndex_020c7a44(int kind);

void Actor_LoadAnimResources(Actor *actor) {
    char path[128];
    NameList names;
    SlotList slots;
    GroupDesc desc;
    int context = actor->playerIndex + 8;
    int i;

    names = gBattleEffectPathParts;
    slots = data_ov059_020cfe10;
    for (i = 0; i < 3; i++) {
        OS_SPrintf(path, sOv059_BaChFormatS_020cff2c, gSoundCategoryNames[actor->state]);
        STD_ConcatenateString(path, names.names[i]);
        AcquireSharedRecordState(&actor->animSlots[slots.slots[i]], path, actor->anim->player, context);
    }
    ZeroBytes0x14(&desc);
    OS_SPrintf(path, sOv059_BaChSoWd00_020cff38);
    desc.count = 1;
    desc.stride = 1;
    desc.fixed = FALSE;
    desc.name = path;
    actor->effectGroupId = func_ov021_020a89c8(&desc);
    LoadActorModel(actor);
    actor->mapKindToSlot = MapKindToSlotIndex_020c7a44;
}
