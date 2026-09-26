extern int GFXi_EnqueueCommand(int a, int b, int c, int d);

typedef struct {
    char _pad[8];
    int f8;
    int fc;
} BG;

int func_0202aed4(int idx, BG *p) {
    if (idx <= 3) return GFXi_EnqueueCommand(0xf, 0, p->fc, p->f8);
    return GFXi_EnqueueCommand(0x1f, 0, p->fc, p->f8);
}
