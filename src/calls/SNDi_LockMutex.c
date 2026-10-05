extern void PM_DeletePreSleepCallback(void *p);
extern int data_02059804;

void SNDi_LockMutex(void) {
    PM_DeletePreSleepCallback(&data_02059804);
}
