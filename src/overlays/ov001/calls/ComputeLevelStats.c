#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 attackRate;
    u16 hpRate;
    u16 modifierRate;
    u16 statRate;
    u16 speed;
    u16 unk_0A;
} StatTableEntry;

typedef struct {
    u8 pad_00[0xc];
    StatTableEntry *data;
} FileSection;

typedef struct {
    u8 pad_00[8];
    FileSection *sections;
} StatFile;

typedef struct {
    u8 pad_00[8];
    s32 value;
    u8 pad_0C[0x13];
    u8 levelScaled;
} StatModifier;

typedef struct {
    s32 hp;
    s32 stats[8];
    u8 pad_24[0xc];
    s32 attack;
    u8 pad_34[0xe];
    u8 fixedHp;
} BaseStats;

typedef struct {
    u8 level;
    u8 pad_01[3];
    s32 maxHp;
    s32 hp;
    s32 stats[8];
    fx32 speed;
    s32 attack;
    StatModifier modifiers[8];
} ActorStats;

extern char sOv001_EnPaBLBin_020a046c[];
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern StatFile *Archive_LoadFile(const char *path, u32 heapId);
extern void RelocateResourceTable(StatFile *file);
extern fx32 FX_Mul(fx32 left, fx32 right);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ComputeLevelStats(ActorStats *out, BaseStats *base, StatModifier *modifiers, u8 level, s16 attackScale, fx32 hpScale)
{
    StatFile *file;
    StatTableEntry *table;
    StatTableEntry *entry;
    u16 i;
    fx32 bonus;

    MI_CpuFill8(out, 0, sizeof(ActorStats));
    file = Archive_LoadFile(sOv001_EnPaBLBin_020a046c, 0xb);
    if (file == NULL) {
        return;
    }
    RelocateResourceTable(file);
    table = file->sections->data;
    out->level = level;
    if (base->fixedHp) {
        out->hp = base->hp;
    } else {
        out->hp = base->hp * table[level].hpRate;
    }
    base->hp = out->maxHp = out->hp = FX_Mul(out->hp, hpScale);
    out->maxHp = out->hp;
    entry = &table[level];
    out->speed = entry->speed << 12;
    out->attack = (base->attack * table[level].attackRate) >> 12;
    out->attack = (out->attack * attackScale) >> 12;
    for (i = 0; i < 8; i++) {
        out->stats[i] = base->stats[i] * table[level].statRate;
    }
    if (out->hp <= 0) {
        out->maxHp = out->hp = 1;
    }
    for (i = 0; i < 8; i++) {
        bonus = 0;
        if (modifiers[i].levelScaled) {
            bonus = entry->modifierRate << 6;
            bonus = FX_Mul(bonus, bonus);
            bonus = FX_Mul(bonus + 0x10000, 0x100) - 0x1000;
        }
        out->modifiers[i] = modifiers[i];
        out->modifiers[i].value = entry->modifierRate * (bonus + modifiers[i].value);
    }
    NNSi_FndFreeFromDefaultHeap(file);
}
