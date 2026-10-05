extern int TP_Init();
extern int TP_GetUserInfo();
extern int TP_SetCalibrateParam();
extern int func_0200fefc();
extern int TP_WaitBusy();
extern int TP_CheckError();

void InitTouchPanel(void) {
    int buf[2];

    TP_Init();
    if (TP_GetUserInfo(buf) != 0) {
        TP_SetCalibrateParam(buf);
    }
    func_0200fefc(9, 0x14);
    TP_WaitBusy(8);
    TP_CheckError(8);
}
