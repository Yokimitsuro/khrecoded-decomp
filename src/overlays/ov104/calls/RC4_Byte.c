typedef unsigned long u32;
typedef unsigned char u8;

typedef struct RC4Context {
    int x;
    int i;
    int j;
    u8 state[256];
} RC4Context;

u8 RC4_Byte(RC4Context *context)
{
    u8 i;
    u8 iValue;
    u8 j;
    u8 jValue;

    i = context->i + 1 + context->x;
    iValue = context->state[i];
    j = iValue + context->j + context->x;
    jValue = context->state[j];

    context->i = i;
    context->j = j;
    context->state[j] = iValue;
    context->state[i] = jValue;

    return context->state[(iValue + jValue) & 0xff];
}