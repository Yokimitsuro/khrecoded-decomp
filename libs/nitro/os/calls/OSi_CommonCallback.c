extern void OS_Terminate(void);
extern unsigned short data_02056b48;

void OSi_CommonCallback(int unused, int status)
{
    if ((unsigned int)((status & 0x7f00) << 8) >> 16 == 0x10) {
        data_02056b48 = 1;
        return;
    }
    OS_Terminate();
}