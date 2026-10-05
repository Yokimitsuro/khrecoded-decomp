extern void func_0204f0d4(void *p, int idx);

void Slot_UnlinkAll(void *p)
{
    int i;
    for (i = 0; i < 0x80; i++) {
        func_0204f0d4(p, i);
    }
}
