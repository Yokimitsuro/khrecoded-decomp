extern int func_02009aa4(void);
extern void CARD_WaitBackupAsync(void);
extern void func_0200923c(int resource, int kind);

void func_020091cc(int resource) {
    if (func_02009aa4() == 0)
        CARD_WaitBackupAsync();
    func_0200923c(resource, 2);
}
