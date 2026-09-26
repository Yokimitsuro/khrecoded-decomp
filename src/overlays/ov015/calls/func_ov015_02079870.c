extern void G2S_GetBG2ScrPtr(int x);
extern int func_ov015_02078f00(void);

int func_ov015_02079870(int x) {
    G2S_GetBG2ScrPtr(x);
    return func_ov015_02078f00();
}
