typedef unsigned long u32;
typedef struct OSExceptionState {
    void *handler;
    u32 reserved04;
    void *originalHandler;
    u32 exceptionOccurred;
} OSExceptionState;
extern OSExceptionState OSi_ExceptionState;
extern void OSi_ExceptionHandler(void);

void OSi_InstallExceptionVector(void)
{
    volatile void **exceptionVector = (volatile void **)0x02fffd9c;
    void *handler = *exceptionVector;

    OSi_ExceptionState.originalHandler = handler;
    OSi_ExceptionState.handler =
        ((u32)handler >= 0x02600000 && (u32)handler < 0x02800000)
            ? handler
            : 0;

    if (OSi_ExceptionState.handler == 0) {
        *exceptionVector = OSi_ExceptionHandler;
        *(volatile void **)((u32)exceptionVector & ~0x00800000) = OSi_ExceptionHandler;
    }

    OSi_ExceptionState.exceptionOccurred = 0;
}