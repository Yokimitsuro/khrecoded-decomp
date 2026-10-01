extern void func_02010a88(void *list, void *info);
extern int data_020597d0;

void PM_DeletePreSleepCallback(void *info)
{
    func_02010a88(&data_020597d0, info);
}