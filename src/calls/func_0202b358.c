extern int LookupPairValue(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*gBgAffineControlDispatch[])(int value, int arg1, int arg2);
extern char data_020555a8;

void func_0202b358(int index, unsigned short *args, int arg1, int arg2) {
    int value = LookupPairValue(&data_020555a8, args[0], args[1]);

    gBgAffineControlDispatch[index](value, arg1, arg2);
}
