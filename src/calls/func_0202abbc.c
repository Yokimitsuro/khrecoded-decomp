extern void MIi_CpuClear32(unsigned int data, void *dst, unsigned int size);
extern unsigned short data_020604fc[];
extern int data_02060504[];

int func_0202abbc(void)
{
    data_020604fc[1] = 0;
    data_020604fc[2] = 0;
    data_020604fc[0] = 0;
    MIi_CpuClear32(0, data_02060504, 0x30);
    return 1;
}
