extern void OS_UnlockMutex(void *mutex);
extern int data_02057c38;

void SNDi_UnlockMutex(void)
{
    OS_UnlockMutex(&data_02057c38);
}