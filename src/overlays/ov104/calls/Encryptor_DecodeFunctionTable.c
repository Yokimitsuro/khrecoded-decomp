typedef unsigned long u32;

typedef struct FuncInfo {
    u32 obfs_addr;
    u32 obfs_size;
} FuncInfo;

extern unsigned char BSS;
extern u32 Encryptor_CategorizeInstruction(u32 instruction);

static inline void clearDataAndInstructionCache(void)
{
    asm {
        mov  ip, #0
        mov  r1, #0
    cacheSetLoop:
        mov  r0, #0
    cacheLineLoop:
        orr  r2, r1, r0
        mcr  p15, 0, ip, c7, c10, 4
        mcr  p15, 0, r2, c7, c14, 2
        add  r0, r0, #0x20
        cmp  r0, #0x400
        blt  cacheLineLoop
        add  r1, r1, #0x40000000
        cmp  r1, #0
        bne  cacheSetLoop
        mov  r0, #0
        mcr  p15, 0, r0, c7, c5, 0
        mcr  p15, 0, ip, c7, c10, 4
    }
}

void Encryptor_DecodeFunctionTable(FuncInfo *functions)
{
    u32 *addr;
    u32 size;
    u32 *end_addr;
    u32 xorval;
    u32 *prevmem;

    prevmem = (u32 *)functions - 3;
    prevmem[0] = prevmem[1] = prevmem[2] = 0;

    do {
        xorval = 0xf0b9a2ea;
        addr = (u32 *)(functions->obfs_addr - 0x1000);
        size = functions->obfs_size - (u32)&BSS - 0x1000;
        end_addr = addr + size / 4;

        for (; addr < end_addr; addr++) {
            switch (Encryptor_CategorizeInstruction(*addr)) {
            case 1:
            case 3:
                {
                    u32 operands = ((*addr & 0x00ffffff) - 0x402) & 0x00ffffff;
                    u32 opcode = (*addr & 0xff000000) ^ 0x01000000;
                    *addr = opcode | operands;
                    xorval ^= *addr >> 24;
                    xorval &= 0x00ffffff;
                }
                break;

            case 2:
                *addr ^= 0x01000000;
            default:
                *addr ^= xorval;
                xorval ^= *addr;
                xorval ^= *addr >> 8;
                xorval &= 0x00ffffff;
                break;
            }
        }

        clearDataAndInstructionCache();
        functions->obfs_addr = functions->obfs_size = 0;
        functions++;
    } while (functions->obfs_addr != 0);
}