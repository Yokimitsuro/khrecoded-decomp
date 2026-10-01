extern unsigned int data_02055bd0[];
extern unsigned int func_02002f20(void);

unsigned int OS_GetConsoleType(void)
{
    if (data_02055bd0[1] != (unsigned int)-1) {
        return data_02055bd0[1];
    }
    data_02055bd0[1] = 0x80000001;
    data_02055bd0[1] |= func_02002f20();
    return data_02055bd0[1];
}
