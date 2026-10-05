extern int LookupPairValue(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*const data_020555f8[])(int value, int flag, int arg1, int arg2);
extern char data_020555c0;

enum { FLAG_CLEAR = 0, FLAG_SET = 1 };

void Cmd_DispatchWithFlag(int index, unsigned short *args, int arg1, int arg2)
{
    int flag = args[2] == 0 ? FLAG_CLEAR : FLAG_SET;
    int value = LookupPairValue(&data_020555c0, args[0], args[1]);

    data_020555f8[index](value, flag, arg1, arg2);
}
