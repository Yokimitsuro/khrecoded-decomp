typedef void (*OSTerminateCallback)(void *arg);

extern void OSi_TerminateCore(void);

void *OSi_TerminateCallbackArg;
OSTerminateCallback OSi_TerminateCallback;

void OS_Terminate(void)
{
    if (OSi_TerminateCallback != 0) {
        OSTerminateCallback callback = OSi_TerminateCallback;
        OSi_TerminateCallback = 0;
        callback(OSi_TerminateCallbackArg);
    }
    OSi_TerminateCore();
}
