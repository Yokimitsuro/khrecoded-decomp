extern void func_0200bd78(int, int);
extern void FSi_WaitForCardThread(int, int);

void func_02029f8c(int a, int b)
{
    FSi_WaitForCardThread(a, b);
    func_0200bd78(a, b);
}
