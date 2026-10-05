extern void *OS_UnlockByWord(int a, void *b, void *c);
extern void OSi_FreeCardBus(void);

void *OS_UnlockCard(unsigned short lockId) {
    return OS_UnlockByWord(lockId, (void *)0x02ffffe0, (void *)OSi_FreeCardBus);
}
