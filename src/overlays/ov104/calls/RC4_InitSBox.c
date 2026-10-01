typedef unsigned long u32;
typedef unsigned char u8;

u32 RC4_InitSBox(u8 *state)
{
    u32 value;
    u32 step;
    u32 *current;
    u32 *end;

    value = 0x03020100;
    step = 0x04040404;
    current = (u32 *)&state[0];
    end = (u32 *)&state[256];
    do {
        *current++ = value ^ 0xffffffff;
        value += step;
    } while (current < end);

    return 0;
}