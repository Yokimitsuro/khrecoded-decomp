extern void UnlinkIntrusiveListNode(void *ptr, void *arg);

void func_0204f0d4(unsigned char *ptr, int index) {
    int offset;
    int *flags;

    if (index < 0) {
        return;
    }

    offset = index * 0x8c;
    flags = (int *)(ptr + 0x7c + offset);
    if (((unsigned int)(*flags << 31) >> 31) == 0) {
        return;
    }

    UnlinkIntrusiveListNode(ptr, ptr + 4 + offset);
    *flags &= ~1;
}
