#include "nitro/types.h"

void CopyIntoWideBuffer(u32 *bufferState, u16 *sourceChars, u32 requestedCount)
{
    u32 charOffset;
    u32 copyCount;
    if ((int)requestedCount > 0) {
        copyCount = bufferState[0];
        if (copyCount > requestedCount) {
            copyCount = requestedCount;
        }
        charOffset = 0;
        if (charOffset < copyCount) {
            do {
                *(u16 *)(bufferState[1] + charOffset * 2) = sourceChars[charOffset];
                charOffset++;
            } while (charOffset < copyCount);
        }
        bufferState[0] = bufferState[0] - copyCount;
        bufferState[1] = bufferState[1] + requestedCount * 2;
    }
}
