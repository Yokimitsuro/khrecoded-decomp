extern void *func_ov039_020bc1dc();
extern void func_ov027_020b902c();
extern void ReleaseIfMarked();

void func_ov078_020c4728(void)
{
    void *p = func_ov039_020bc1dc();
    func_ov027_020b902c(p);
    ReleaseIfMarked(p);
}
