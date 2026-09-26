extern int func_0200494c();
extern void OS_RestoreInterrupts(int mask);
extern int *data_02057c50[];

int func_0200f354(void) {
    int mask;
    int count;
    int *p;
    mask = func_0200494c();
    count = 0;
    p = data_02057c50[2];
    if (p != 0) {
        do {
            p = (int *)*p;
            count++;
        } while (p != 0);
    }
    OS_RestoreInterrupts(mask);
    return count;
}
