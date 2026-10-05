#include "nitro/types.h"

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern int ReadCardBackupSync(int mode, void *buffer, int size);
extern int CompareByteStrings(unsigned char *leftBytes, unsigned char *rightBytes, int length);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct {
    u8 pad_00[4];
    u8 *referenceBytes;
} IdTable;

extern IdTable gGameTitleStringTable;

int VerifyCardIdMatchesReference(void)
{
    void *buffer;
    int result;
    int status;
    u8 *reference;
    int count;
    int offset;
    int cmpResult;

    buffer = NNS_FndAllocFromDefaultExpHeapEx(0x20, 0x20);
    result = 0;
    status = ReadCardBackupSync(0, buffer, 0x20);
    if (status == 0) {
        reference = gGameTitleStringTable.referenceBytes;
        count = 0;
        offset = 0;
        do {
            cmpResult = CompareByteStrings((u8 *)buffer + offset, reference, 8);
            if (cmpResult != 0) {
                break;
            }
            count = count + 1;
            offset = offset + 8;
        } while (count < 4);
        result = 1;
        if (count != 4) {
            result = 0;
        }
    }
    NNSi_FndFreeFromDefaultHeap(buffer);
    return result;
}
