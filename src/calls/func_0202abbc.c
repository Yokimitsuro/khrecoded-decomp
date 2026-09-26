extern void func_01ff86fc(unsigned int data, void *dst, unsigned int size);
extern unsigned short data_020604fc[];
extern int data_02060504[];

int func_0202abbc(void)
{
    data_020604fc[1] = 0;
    data_020604fc[2] = 0;
    data_020604fc[0] = 0;
    func_01ff86fc(0, data_02060504, 0x30);
    return 1;
}
