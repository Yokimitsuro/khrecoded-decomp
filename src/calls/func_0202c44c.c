extern void OS_SleepThread(void *p);
extern struct { char _0[4]; char *field_4; char _8[0x34]; int field_3c; } gFileLoader;

int func_0202c44c(void)
{
    if (gFileLoader.field_3c <= 0) {
        if (*(int *)(gFileLoader.field_4 + 0x448) == 0) goto out;
    }
    OS_SleepThread(gFileLoader.field_4 + 0x4c + 0x400);
out:
    return 1;
}
