#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct UnitRecord {
    fx32 speed;
    s16 angles[4];
    u32 turnRate : 16;
    u32 unk_0c_hi : 16;
    u8 nibbles[11];
    u8 bytesA[4];
    u8 bytesB[8];
    u8 pad_27;
} UnitRecord;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0208723c(int group);
extern void StoreFieldUnitEntry(void *unit, int index, const UnitRecord *src);

int ScriptCmd_StoreFieldUnitRecord(void *vm, ScriptOperand *op)
{
    int group = ScriptVm_ReadOperandInt(vm, op++);
    int index = ScriptVm_ReadOperandInt(vm, op++);
    UnitRecord record;
    u32 nibblesLo;
    u32 nibblesHi;
    u32 wordA;
    u32 wordB;
    u32 i;
    u32 wordC;

    record.speed = ScriptVm_ReadOperandFx32(vm, op++);
    record.angles[0] = ScriptVm_ReadOperandFx32(vm, op++) * 30 / 4096;
    record.angles[1] = ScriptVm_ReadOperandFx32(vm, op++) * 30 / 4096;
    record.angles[2] = ScriptVm_ReadOperandFx32(vm, op++) * 30 / 4096;
    record.angles[3] = ScriptVm_ReadOperandFx32(vm, op++) * 30 / 4096;
    record.turnRate = ScriptVm_ReadOperandFx32(vm, op++) * 30 / 4096;
    nibblesLo = ScriptVm_ReadOperandInt(vm, op++);
    nibblesHi = ScriptVm_ReadOperandInt(vm, op++);
    wordA = ScriptVm_ReadOperandInt(vm, op++);
    wordB = ScriptVm_ReadOperandInt(vm, op++);
    wordC = ScriptVm_ReadOperandInt(vm, op++);

    for (i = 0; i < sizeof(record.nibbles); i++) {
        if ((int)i < 8) {
            record.nibbles[i] = nibblesLo & 0xf;
            nibblesLo >>= 4;
        } else {
            record.nibbles[i] = nibblesHi & 0xf;
            nibblesHi >>= 4;
        }
    }
    for (i = 0; i < sizeof(record.bytesA); i++) {
        record.bytesA[i] = wordA;
        wordA >>= 8;
    }
    for (i = 0; i < sizeof(record.bytesB); i++) {
        if ((int)i < 4) {
            record.bytesB[i] = wordB;
            wordB >>= 8;
        } else {
            record.bytesB[i] = wordC;
            wordC >>= 8;
        }
    }
    StoreFieldUnitEntry(func_ov001_0208723c(group), index, &record);
    return 1;
}
