typedef unsigned long u32;
typedef unsigned char u8;

typedef struct RC4Context {
    int x;
    int i;
    int j;
    u8 state[256];
} RC4Context;

extern u8 RC4_Byte(RC4Context *context);
extern u32 RC4_InitSBox(u8 *state);
extern u32 Encryptor_CategorizeInstruction(u32 instruction);

static inline void decryptByte(RC4Context *context, u8 *source, u8 *destination)
{
    int decryptedByte = RC4_Byte(context) ^ *source;
    context->x = *source;
    *destination = decryptedByte;
}

u32 RC4_DecryptInstructions(RC4Context *context, void *source, void *destination, u32 size)
{
    u8 state[256];
    u32 offset;
    u32 instruction;
    u8 *sourceBytes;
    u8 *destinationBytes;

    if (size & 3) {
        return -1;
    }

    sourceBytes = (u8 *)source;
    destinationBytes = (u8 *)destination;
    RC4_InitSBox(state);

    for (offset = 0; offset < size; offset += 4) {
        instruction = *(u32 *)(sourceBytes + offset);
        switch (Encryptor_CategorizeInstruction(instruction)) {
        case 1:
        case 3:
            {
                u32 opcode;
                u32 operands;
                u32 *destinationAddress = (u32 *)(destinationBytes + offset);

                context->x += instruction >> 24;
                opcode = (instruction & 0xff000000) ^ 0x01000000;
                operands = ((instruction & 0x00ffffff) - 0x402) & 0x00ffffff;
                *destinationAddress = opcode | operands;
            }
            break;

        case 2:
            decryptByte(context, sourceBytes + offset, destinationBytes + offset);
            decryptByte(context, sourceBytes + offset + 1, destinationBytes + offset + 1);
            context->x = sourceBytes[offset + 2] * context->x - sourceBytes[offset + 3];
            destinationBytes[offset + 2] = state[sourceBytes[offset + 2]];
            destinationBytes[offset + 3] = sourceBytes[offset + 3];
            *(u32 *)(sourceBytes + offset) ^= 0x01000000;
            break;

        default:
            decryptByte(context, sourceBytes + offset, destinationBytes + offset);
            decryptByte(context, sourceBytes + offset + 1, destinationBytes + offset + 1);
            context->x = sourceBytes[offset + 2] * context->x - sourceBytes[offset + 3];
            destinationBytes[offset + 2] = state[sourceBytes[offset + 2]];
            destinationBytes[offset + 3] = sourceBytes[offset + 3];
            break;
        }
    }

    return 0;
}