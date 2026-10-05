extern void func_0202756c(int enabled);
extern void SetPendingScene(int mode, int value);

void DSProt_OnDetection(void) {
    func_0202756c(1);
    SetPendingScene(2, 0);
}
