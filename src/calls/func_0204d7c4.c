extern unsigned char *GetRecentHistoryEntry(int arg);
extern void PushSoundQueueEntry(int arg0, int arg1, int arg2);

int func_0204d7c4(int arg) {
    unsigned char *ptr = GetRecentHistoryEntry(0);

    if (ptr == 0 || ptr[0] != 1) {
        PushSoundQueueEntry(1, arg, 0);
    } else {
        ptr[1] = arg;
    }

    return 1;
}
