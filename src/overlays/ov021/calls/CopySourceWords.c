#include "nitro/types.h"

typedef struct WordSource {
    u8 pad_00[8];
    u32 words[11];
} WordSource;

typedef struct WordCache {
    u8 pad_00[0x10];
    WordSource *source;
    int dirty;
    u8 pad_18[0x58];
    u32 words[11];
} WordCache;

void CopySourceWords(WordCache *cache)
{
    int i;
    for (i = 0; i < 11; i++) {
        cache->words[i] = cache->source->words[i];
    }
    cache->dirty = 0;
}
