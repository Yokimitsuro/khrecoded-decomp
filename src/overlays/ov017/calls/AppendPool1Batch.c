#include "nitro/types.h"

typedef struct BatchSource {
    u32 words[3];
} BatchSource;

extern u16 AppendPool1Entry(void *manager, BatchSource *source, int mode, int arg0, int arg1);

void AppendPool1Batch(void *manager, int count, BatchSource *sources, int arg1, int arg0, u16 *outIndices)
{
    int i;
    u16 index;

    for (i = 0; i < count; i++) {
        index = AppendPool1Entry(manager, &sources[i], 1, arg0, arg1);
        if (outIndices != NULL) {
            outIndices[i] = index;
        }
    }
}
