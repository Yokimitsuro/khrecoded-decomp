extern unsigned int OS_GetConsoleType(void);

int CommandPort_IsEnabled(void)
{
    return (OS_GetConsoleType() & 0x10000000) != 0;
}
