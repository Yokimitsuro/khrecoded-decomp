#include "nitro/types.h"

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int WriteCardBackupSync(u32 backupOffset, void *buffer, u32 length);
extern const void *gGameTitleStringTable;

BOOL FormatCardBackup(void)
{
    int block;
    int offset;
    BOOL success = TRUE;
    u8 *header = NNS_FndAllocFromDefaultExpHeapEx(0x20, 0x20);
    int slot;
    int copy;

    MIi_CpuClearFast(0, header, 0x20);
    for (slot = 0; slot < 2; slot++) {
        for (block = 0; block < 2; block++) {
            if (WriteCardBackupSync((block + slot * 2) * 0x3c18 + 0x20, header, 0x20) != 0) {
                success = FALSE;
                goto done;
            }
        }
    }
    for (offset = 0, copy = 0; copy < 4; copy++, offset += 8) {
        MI_CpuCopy8(gGameTitleStringTable, header + offset, 8);
    }
    if (WriteCardBackupSync(0, header, 0x20) != 0) {
        success = FALSE;
    }
done:
    NNSi_FndFreeFromDefaultHeap(header);
    return success;
}
