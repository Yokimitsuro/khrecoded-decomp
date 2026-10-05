#include "nitro/types.h"

void FillWideBuffer(u32 *bufferState, u16 fillValue, u32 requestedCount)
{
    u32 charOffset;
    u32 writeCount;
    if ((int)requestedCount > 0) {
        writeCount = bufferState[0];
        if (writeCount > requestedCount) {
            writeCount = requestedCount;
        }
        charOffset = 0;
        if (charOffset < writeCount) {
            do {
                *(u16 *)(bufferState[1] + charOffset * 2) = fillValue;
                charOffset++;
            } while (charOffset < writeCount);
        }
        bufferState[0] = bufferState[0] - writeCount;
        bufferState[1] = bufferState[1] + requestedCount * 2;
    }
}
