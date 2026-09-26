extern void func_0200bdcc(int, int);
extern void FSi_WaitForCardThread(int, int);

void func_02029fac(int a, int b)
{
    FSi_WaitForCardThread(a, b);
    func_0200bdcc(a, b);
}
