extern int func_02013dc4(void *q);
extern void *func_02013f98(void *q);
extern void func_02013f4c(void *q);

extern char data_0205a8d0[];

struct Node {
    void *x0;
    int x4;
    int x8;
    int xc;
};

struct Q {
    char _0[0x10];
    int x10;
};

int GFXi_EnqueueCommand(void *a, int b, int c, int d)
{
    struct Node *n;
    struct Q *q = (struct Q *)data_0205a8d0;
    if (func_02013dc4(q) != 0) return 0;
    n = (struct Node *)func_02013f98(q);
    n->x0 = a;
    n->x4 = c;
    n->x8 = b;
    n->xc = d;
    func_02013f4c(q);
    q->x10 = q->x10 + n->xc;
    return 1;
}
