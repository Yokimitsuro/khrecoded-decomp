extern void func_020032a8(void *mutex, unsigned int lockBit);

void OS_UnlockMutex(void *mutex)
{
    func_020032a8(mutex, 0x10000000);
}