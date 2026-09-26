extern int func_02009aa4(void);
extern void func_02009a9c(void);
extern void func_0200923c(int resource, int kind);

void func_020091cc(int resource) {
    if (func_02009aa4() == 0)
        func_02009a9c();
    func_0200923c(resource, 2);
}
