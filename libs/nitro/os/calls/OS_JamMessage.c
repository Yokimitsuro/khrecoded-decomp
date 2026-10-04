typedef int BOOL;
typedef int s32;
typedef int OSIntrMode;
typedef void *OSMessage;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage *messages;
    s32 messageCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

#define OS_MESSAGE_BLOCK 1

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
extern void OS_SleepThread(OSThreadQueue *queue);
extern void OS_WakeupThread(OSThreadQueue *queue);
BOOL OS_JamMessage(OSMessageQueue *queue, OSMessage message, s32 flags)
{
    OSIntrMode interruptMode = OS_DisableInterrupts();

    while (queue->messageCount <= queue->usedCount) {
        if (!(flags & OS_MESSAGE_BLOCK)) {
            (void)OS_RestoreInterrupts(interruptMode);
            return 0;
        } else {
            OS_SleepThread(&queue->queueSend);
        }
    }

    queue->firstIndex =
        (queue->firstIndex + queue->messageCount - 1) % queue->messageCount;
    queue->messages[queue->firstIndex] = message;
    queue->usedCount++;
    OS_WakeupThread(&queue->queueReceive);

    (void)OS_RestoreInterrupts(interruptMode);
    return 1;
}