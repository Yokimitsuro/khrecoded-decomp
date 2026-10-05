extern void NotifyFlaggedActors(void);
extern void DrawScreenFadeQuad(void);
extern void func_ov001_020887a4(void);
void func_ov001_02088570(void)
{
    NotifyFlaggedActors();
    DrawScreenFadeQuad();
    func_ov001_020887a4();
}
