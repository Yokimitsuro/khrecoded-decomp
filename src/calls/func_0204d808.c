extern unsigned char *GetRecentHistoryEntry(int arg);
extern void PushSoundQueueEntry(int arg0, int arg1, int arg2);

void func_0204d808(int arg) {
    unsigned char *ptr = GetRecentHistoryEntry(0);

    if (ptr == 0 || ptr[0] != 3) {
        PushSoundQueueEntry(3, 0, (unsigned short)arg);
        return;
    }

    *(unsigned short *)(ptr + 2) = arg;
}
