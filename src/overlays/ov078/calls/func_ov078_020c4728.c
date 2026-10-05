extern void *func_ov039_020bc1dc();
extern void DestroyAllContainerElements();
extern void ReleaseIfMarked();

void func_ov078_020c4728(void)
{
    void *p = func_ov039_020bc1dc();
    DestroyAllContainerElements(p);
    ReleaseIfMarked(p);
}
