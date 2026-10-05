extern int OSi_FreeStackAlloc();

int StackAlloc_FreeIfSetB(int a) {
    if (a) OSi_FreeStackAlloc(a);
}
