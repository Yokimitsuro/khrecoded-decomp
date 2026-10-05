#include "nitro/types.h"

typedef struct QueuedSound {
    u16 first;
    u16 second;
} QueuedSound;

extern char *data_0206084c;

void PopQueuedSound(void)
{
    char *base = data_0206084c;

    if (*(u8 *)(base + 0xb47d3) == 0) {
        *(u8 *)(base + 0xb47be) = 0;
        return;
    }

    *(QueuedSound *)(base + 0xb47be) = *(QueuedSound *)(base + *(u8 *)(base + 0xb47d2) * 4 + 0xb47c2);

    /* Advance the four-slot ring head */
    *(u8 *)(base + 0xb47d2) = (*(u8 *)(base + 0xb47d2) + 1) % 4;
    *(u8 *)(base + 0xb47d3) = *(u8 *)(base + 0xb47d3) - 1;
}
