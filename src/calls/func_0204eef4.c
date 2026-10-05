/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void NNSi_FndFreeFromDefaultHeap(void *p);

struct Node02032334 {
    char _0[0x14];
    void *field_14;
    void *field_18;
    void *field_1c;
};

void func_0204eef4(struct Node02032334 *p)
{
    if (p->field_1c != 0) {
        NNSi_FndFreeFromDefaultHeap(p->field_1c);
    } else {
        if (p->field_14 != 0)
            NNSi_FndFreeFromDefaultHeap(p->field_14);
        if (p->field_18 != 0)
            NNSi_FndFreeFromDefaultHeap(p->field_18);
    }
    p->field_1c = 0;
    p->field_18 = 0;
    p->field_14 = 0;
}
