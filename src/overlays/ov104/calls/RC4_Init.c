typedef unsigned long u32;
typedef unsigned char u8;

typedef struct RC4Context {
    int x;
    int i;
    int j;
    u8 state[256];
} RC4Context;

void RC4_Init(RC4Context *context, const void *key, u32 keyLength)
{
    u8 first;
    u8 second;
    int i;
    u8 stateIndex;
    int keyIndex;
    u32 *stateStart;
    u32 *stateEnd;
    u32 value;
    u32 step;

    keyIndex = 0;
    stateIndex = 0;
    context->x = 0xaa;
    context->i = 0;
    context->j = 0;

    stateStart = (u32 *)&context->state[0];
    stateEnd = (u32 *)&context->state[256];
    value = 0x03020100;
    step = 0x04040404;
    do {
        *stateStart++ = value;
        value += step;
    } while (stateStart < stateEnd);

    for (i = 255; i >= 0; i--) {
        first = context->state[i];
        stateIndex = stateIndex + ((u8 *)key)[keyIndex] + first;
        second = context->state[stateIndex];
        context->state[stateIndex] = first;
        context->state[i] = second;
        keyIndex++;
        if (keyIndex >= keyLength) {
            keyIndex = 0;
        }
    }
}