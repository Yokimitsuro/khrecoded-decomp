extern void OS_Terminate(void);
extern unsigned short OSi_IsResetOccurred;

void OSi_CommonCallback(int unused, int status)
{
    if ((unsigned int)((status & 0x7f00) << 8) >> 16 == 0x10) {
        OSi_IsResetOccurred = 1;
        return;
    }
    OS_Terminate();
}