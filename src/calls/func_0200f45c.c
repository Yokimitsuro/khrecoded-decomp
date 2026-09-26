extern int func_0200494c();
extern void OS_RestoreInterrupts(int mask);
extern int *data_02057c50[];

int *func_0200f45c(void) {
    int mask;
    int *h;
    int *n;
    mask = func_0200494c();
    h = data_02057c50[0];
    if (h == 0) {
        OS_RestoreInterrupts(mask);
        return 0;
    }
    n = (int *)*h;
    data_02057c50[0] = n;
    if (n == 0) data_02057c50[4] = 0;
    OS_RestoreInterrupts(mask);
    return h;
}
