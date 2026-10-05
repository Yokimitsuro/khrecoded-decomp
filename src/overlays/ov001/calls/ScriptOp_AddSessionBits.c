#include "nitro/types.h"

typedef struct ScriptVm {
    u8 pad_000[0x640];
    u32 (*readBits)(u16 bitOffset, int bitCount);
    void (*writeBits)(u16 bitOffset, int bitCount, u32 value);
} ScriptVm;

typedef struct ScriptCommand {
    u32 opcode;
    u32 bitOffset;
    u8 countOperand[8];
    u8 amountOperand[8];
} ScriptCommand;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);

int ScriptOp_AddSessionBits(ScriptVm *vm, ScriptCommand *command)
{
    u16 bitOffset = command->bitOffset;
    int bitCount = ScriptVm_ReadOperandInt(vm, command->countOperand);
    int amount = ScriptVm_ReadOperandInt(vm, command->amountOperand);
    u32 total = amount + vm->readBits(bitOffset, bitCount);

    if (total <= (1 << bitCount) - 1) {
        vm->writeBits(bitOffset, bitCount, total);
    }
    return 1;
}
