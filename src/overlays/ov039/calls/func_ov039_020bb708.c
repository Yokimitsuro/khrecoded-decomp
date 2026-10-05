extern int GetStateC9C4(void);
extern void (*data_ov039_020be7bc[])(void);
void func_ov039_020bb708(void)
{
    void (*callback)(void) = data_ov039_020be7bc[GetStateC9C4()];
    if (callback != 0) {
        callback();
    }
}
