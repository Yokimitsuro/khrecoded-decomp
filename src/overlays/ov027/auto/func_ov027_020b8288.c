void func_ov027_020b8288(char *obj, void *arg) {
    void (*fp)(void *) = *(void (**)(void *))(obj + 0x40);
    if (fp) {
        fp(arg);
    }
}
