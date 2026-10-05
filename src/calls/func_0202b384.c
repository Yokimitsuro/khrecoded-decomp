extern int LookupPairValue(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*gBgExtendedControlDispatch[])(int value, int arg1, int arg2);
extern char data_02055590;

void func_0202b384(int index, unsigned short *args, int arg1, int arg2) {
    int value = LookupPairValue(&data_02055590, args[0], args[1]);

    gBgExtendedControlDispatch[index](value, arg1, arg2);
}
