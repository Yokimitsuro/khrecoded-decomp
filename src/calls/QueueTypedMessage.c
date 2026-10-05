extern void *AllocLoaderRequest(void);
extern void OS_SendMessage(void *queue, void *message, int flags);

extern int data_02060584;

typedef struct {
    char _0[4];
    int type;
    unsigned short message_id;
    char _a[2];
    int message_argument_1;
    int message_argument_2;
} QueuedMessage;

void QueueTypedMessage(unsigned short message_id, int message_argument_1, int message_argument_2)
{
    QueuedMessage *queued_entry = AllocLoaderRequest();

    if (queued_entry == 0)
        return;

    queued_entry->type = 2;
    queued_entry->message_id = message_id;
    queued_entry->message_argument_1 = message_argument_1;
    queued_entry->message_argument_2 = message_argument_2;
    OS_SendMessage(&data_02060584, queued_entry, 1);
}
