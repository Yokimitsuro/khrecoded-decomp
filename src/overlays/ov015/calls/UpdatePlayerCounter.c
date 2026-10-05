#include "nitro/types.h"

extern int DispatchContextCommand(int a, int b, int c, int d);
extern unsigned int func_0202a9e4(unsigned int range);
extern int data_ov015_0207e960;

void UpdatePlayerCounter(void)
{
    int index;
    int counter;
    int cap;

    counter = DispatchContextCommand(4, 0, 0, 0) + 1;
    cap = func_0202a9e4(200);
    if (counter > cap) {
        DispatchContextCommand(0x80000005, 1, 0, 0);
        counter = 0;
    }
    index = *(int *)(data_ov015_0207e960 + 0xec);
    if (*(u8 *)(index * 0x70 + data_ov015_0207e960 + 0xcfbc) != 0 && func_0202a9e4(100) == 0x32) {
        counter = 0;
        DispatchContextCommand(0x80000005, 1, 0, 0);
    }
    DispatchContextCommand(0x80000004, counter, 0, 0);
}
