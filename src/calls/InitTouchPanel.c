extern int TP_Init();
extern int func_0200fcd0();
extern int func_0200fd4c();
extern int func_0200fefc();
extern int TP_WaitBusy();
extern int TP_CheckError();

void InitTouchPanel(void) {
    int buf[2];

    TP_Init();
    if (func_0200fcd0(buf) != 0) {
        func_0200fd4c(buf);
    }
    func_0200fefc(9, 0x14);
    TP_WaitBusy(8);
    TP_CheckError(8);
}
