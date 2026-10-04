typedef unsigned long u32;

typedef struct OSThread OSThread;

struct OSThread {
    unsigned char context[0x64];
    int state;
    OSThread *next;
    u32 id;
    u32 priority;
};

typedef struct OSThreadSystemState {
    unsigned char reserved000[0x24];
    OSThread *list;
} OSThreadSystemState;

extern OSThreadSystemState OSi_ThreadSystemState;

void OSi_InsertThreadToList(OSThread *thread)
{
    OSThread *current = OSi_ThreadSystemState.list;
    OSThread *previous = 0;

    while (current && current->priority < thread->priority) {
        previous = current;
        current = current->next;
    }

    if (!previous) {
        thread->next = OSi_ThreadSystemState.list;
        OSi_ThreadSystemState.list = thread;
    } else {
        thread->next = previous->next;
        previous->next = thread;
    }
}