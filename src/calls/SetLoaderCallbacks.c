#include "nitro/types.h"

extern void ReadGlobalPackedBits(void);
extern void WriteGlobalPackedBits(void);

void SetLoaderCallbacks(int context, int writeHandler, int readHandler)
{
    if (writeHandler != 0) {
        *(int *)(context + 0x644) = writeHandler;
    } else {
        *(int *)(context + 0x644) = (int)WriteGlobalPackedBits;
    }

    if (readHandler != 0) {
        *(int *)(context + 0x640) = readHandler;
        return;
    }
    *(int *)(context + 0x640) = (int)ReadGlobalPackedBits;
}
