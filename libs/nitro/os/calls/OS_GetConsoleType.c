extern unsigned int data_02055bd0[];
extern unsigned int OSi_DetectDeviceType(void);

unsigned int OS_GetConsoleType(void)
{
    if (data_02055bd0[1] != (unsigned int)-1) {
        return data_02055bd0[1];
    }
    data_02055bd0[1] = 0x80000001;
    data_02055bd0[1] |= OSi_DetectDeviceType();
    return data_02055bd0[1];
}
