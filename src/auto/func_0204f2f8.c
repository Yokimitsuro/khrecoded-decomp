struct S { char pad[0x7c]; int flags; char pad2[0x8c - 0x80]; };

void func_0204f2f8(struct S *base, int index)
{
    if (index < 0) return;
    base[index].flags &= ~2;
}
