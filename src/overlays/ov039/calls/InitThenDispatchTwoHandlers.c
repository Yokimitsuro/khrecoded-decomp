extern int data_ov039_020bea20;
extern void func_ov039_020baf3c(void);
extern void func_ov039_020bcf40(int arg0);
extern void func_ov039_020bd074(int arg0);

void InitThenDispatchTwoHandlers(void)
{
    func_ov039_020baf3c();
    func_ov039_020bcf40(*(int *)(data_ov039_020bea20 + 0xc998));
    func_ov039_020bd074(*(int *)(data_ov039_020bea20 + 0xc99c));
}
