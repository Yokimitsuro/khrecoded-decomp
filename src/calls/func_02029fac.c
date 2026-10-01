extern void FS_UnloadOverlay(int, int);
extern void FSi_WaitForCardThread(int, int);

void func_02029fac(int a, int b)
{
    FSi_WaitForCardThread(a, b);
    FS_UnloadOverlay(a, b);
}
