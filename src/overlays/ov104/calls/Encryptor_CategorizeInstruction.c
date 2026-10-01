typedef unsigned long u32;
typedef unsigned char u8;

enum {
    INS_TYPE_OTHER = 0,
    INS_TYPE_BLXIMM,
    INS_TYPE_BL,
    INS_TYPE_B
};

u32 Encryptor_CategorizeInstruction(u32 instruction)
{
    u8 opcode = instruction >> 24;

    if ((opcode & 0x0e) == 0x0a) {
        if ((opcode & 0xf0) == 0xf0) {
            return INS_TYPE_BLXIMM;
        }
        if (opcode & 1) {
            return INS_TYPE_BL;
        }
        return INS_TYPE_B;
    }

    return INS_TYPE_OTHER;
}