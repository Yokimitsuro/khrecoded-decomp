typedef struct OSThread OSThread;

struct OSThread {
    unsigned char reserved000[0x68];
    OSThread *next;
};

typedef struct OSThreadSystemState {
    unsigned char reserved000[0x24];
    OSThread *list;
} OSThreadSystemState;

extern OSThreadSystemState OSi_ThreadSystemState;

void OSi_RemoveThreadFromList(OSThread *thread)
{
    OSThread *current = OSi_ThreadSystemState.list;
    OSThread *previous = 0;

    while (current && current != thread) {
        previous = current;
        current = current->next;
    }

    if (!previous) {
        OSi_ThreadSystemState.list = thread->next;
    } else {
        previous->next = thread->next;
    }
}