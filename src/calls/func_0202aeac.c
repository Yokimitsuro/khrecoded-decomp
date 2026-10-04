extern int NNS_GfdRegisterNewVramTransferTask(int a, int b, int c, int d);

typedef struct {
    char _pad[8];
    int f8;
    int fc;
} BG;

int func_0202aeac(int idx, BG *p) {
    int sh = idx << 13;
    if (idx <= 3) return NNS_GfdRegisterNewVramTransferTask(0x11, sh, p->fc, p->f8);
    return NNS_GfdRegisterNewVramTransferTask(0x21, sh - 0x8000, p->fc, p->f8);
}
