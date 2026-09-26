static inline void ZeroIp(void) { asm { mov ip, #0 } }
static inline void DrainWriteBuffer(void) { asm { mcr p15, 0, ip, c7, c10, 4 } }
static inline void CleanAndInvalidateDCacheLine(void *addr) { asm { mcr p15, 0, addr, c7, c14, 1 } }

void DC_FlushRange(void *address, unsigned int size)
{
    int end;
    void *line;

    ZeroIp();
    end = (int)size + (int)address;
    line = (void *)((unsigned int)address & ~0x1f);
    do {
        DrainWriteBuffer();
        CleanAndInvalidateDCacheLine(line);
        line = (char *)line + 0x20;
    } while ((int)line < end);
}
