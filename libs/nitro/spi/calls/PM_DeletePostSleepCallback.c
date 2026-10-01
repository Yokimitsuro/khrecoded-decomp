extern void func_02010a88(void *list, void *info);
extern int data_020597d8;

void PM_DeletePostSleepCallback(void *info)
{
    func_02010a88(&data_020597d8, info);
}