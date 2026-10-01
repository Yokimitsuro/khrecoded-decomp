extern void NNSi_FndFreeFromDefaultHeap();
extern int data_ov040_020be284;

void func_ov040_020be00c(void) {
    if (data_ov040_020be284 != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov040_020be284);
    }
    data_ov040_020be284 = 0;
}
