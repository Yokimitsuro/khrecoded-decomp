extern int func_0202c4a0(int param2, int type);
extern void func_ov027_020b77a0(int ctx, int section);
extern void func_ov027_020b77e0(int ctx, int section);
extern void func_ov027_020b7848(int ctx, int section);
extern void func_0202a1d8(int ptr);
void func_ov027_020b7e44(int ctx, int param2) {
    int *buf = (int *)func_0202c4a0(param2, 0xe);
    int a = buf[0], c = buf[2], b = buf[1];
    func_ov027_020b77a0(ctx, (int)buf + a);
    func_ov027_020b77e0(ctx, (int)buf + b);
    func_ov027_020b7848(ctx, (int)buf + c);
    if (buf != 0) {
        func_0202a1d8((int)buf);
    }
}
