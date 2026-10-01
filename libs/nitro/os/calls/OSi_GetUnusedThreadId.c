typedef unsigned int u32;

typedef struct OSThreadState {
    unsigned char padding00[0x18];
    u32 nextThreadId;
} OSThreadState;

extern OSThreadState data_02056b50;

int OSi_GetUnusedThreadId(void)
{
    data_02056b50.nextThreadId++;
    return data_02056b50.nextThreadId;
}