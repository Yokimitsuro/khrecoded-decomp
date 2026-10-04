extern unsigned int NNS_G2dGetAnimSequenceByIdx(unsigned int a, unsigned int b);
extern void func_02015774(void *p, unsigned int v, void *q);

void func_0204e564(void *p, unsigned int a, void *q, int b)
{
    unsigned int v;
    if (b < 0) return;
    v = NNS_G2dGetAnimSequenceByIdx(a, (unsigned int)(unsigned short)b);
    func_02015774(p, v, q);
}
