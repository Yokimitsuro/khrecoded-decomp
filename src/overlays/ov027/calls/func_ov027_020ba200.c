typedef unsigned int u32;

extern char *data_ov027_020ba3e4;
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void func_0202a1d8(void *block);

void func_ov027_020ba200(char *self, int freeOwned) {
    u32 buffer;

    NNS_FndRemoveListObject(data_ov027_020ba3e4 + 0xc, self);
    if (freeOwned != 0 && *(void **)(self + 8) != 0) {
        func_0202a1d8(*(void **)(self + 8));
        *(void **)(self + 8) = 0;
    }
    buffer = *(u32 *)(self + 4);
    if ((buffer & 0x80000000) != 0) {
        *(u32 *)(self + 4) = 0;
    } else if (buffer != 0) {
        func_0202a1d8((void *)buffer);
        *(u32 *)(self + 4) = 0;
    }
    if (self != 0) {
        func_0202a1d8(self);
    }
}
