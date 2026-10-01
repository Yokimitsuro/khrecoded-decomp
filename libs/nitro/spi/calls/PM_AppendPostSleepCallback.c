extern void func_02010a30(void *list, void *info, unsigned int position, int prepend);
extern int data_020597d8;

void PM_AppendPostSleepCallback(void *info)
{
    func_02010a30(&data_020597d8, info, 0xff, 0);
}