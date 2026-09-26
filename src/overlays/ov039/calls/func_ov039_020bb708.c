extern int func_ov039_020bab18(void);
extern void (*data_ov039_020be7bc[])(void);
void func_ov039_020bb708(void)
{
    void (*callback)(void) = data_ov039_020be7bc[func_ov039_020bab18()];
    if (callback != 0) {
        callback();
    }
}
