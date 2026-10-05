extern void WH_SetError(unsigned int id);
extern int func_ov015_02073d1c(void);
extern void PollPanelTransition(void);

void func_ov015_02073cec(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        WH_SetError(*(unsigned short *)(req + 2));
        PollPanelTransition();
        return;
    }
    if (func_ov015_02073d1c() != 0) {
        return;
    }
    PollPanelTransition();
}
