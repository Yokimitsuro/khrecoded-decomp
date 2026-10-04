typedef struct OSThread OSThread;

struct OSThread {
    unsigned char reserved000[0x64];
    int state;
    OSThread *next;
};

typedef struct OSThreadSystemState {
    unsigned char reserved000[0x24];
    OSThread *list;
} OSThreadSystemState;

extern OSThreadSystemState OSi_ThreadSystemState;

#define OS_THREAD_STATE_READY 1

OSThread *OS_SelectThread(void)
{
    OSThread *thread = OSi_ThreadSystemState.list;

    while (thread && thread->state != OS_THREAD_STATE_READY) {
        thread = thread->next;
    }

    return thread;
}