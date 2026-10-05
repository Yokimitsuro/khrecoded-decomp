extern int RunTransitionSlot9(void *handler);
extern void WH_SetError(int id);
extern void HandlePanelPromptSelection(int req);

int func_ov015_02073d1c(void) {
    int r = RunTransitionSlot9(&HandlePanelPromptSelection);
    if (r != 2) {
        WH_SetError(r);
        return 0;
    }
    return 1;
}
