typedef unsigned int u32;

typedef struct OSThreadState {
    unsigned char padding00[0x18];
    u32 nextThreadId;
} OSThreadState;

extern OSThreadState OSi_ThreadSystemState;

int OSi_GetUnusedThreadId(void)
{
    OSi_ThreadSystemState.nextThreadId++;
    return OSi_ThreadSystemState.nextThreadId;
}