extern void HandleSbcNoOp(void);
extern void HandleSbcReturn(void);
extern void func_01ffe280(void);
extern void func_01ffe394(void);
extern void func_01ffe3d8(void);
extern void func_01ffe8a0(void);
extern void func_01ffe934(void);
extern void NNSi_G3dFuncSbc_BB(void);
extern void NNSi_G3dFuncSbc_RollBB(void);
extern void func_01ffec28(void);
extern void Sbc_CallDl(void);
extern void func_01fff374(void);
extern void NNSi_G3dFuncSbc_ENVMAP(void);
extern void NNSi_G3dFuncSbc_PRJMAP(void);
extern void func_01ffa1f4(unsigned seed);
extern void *data_027e01f8[];

void InitializeArchiveBackend(void) {
    data_027e01f8[0] = (void *)&HandleSbcNoOp;
    data_027e01f8[1] = (void *)&HandleSbcReturn;
    data_027e01f8[2] = (void *)&func_01ffe280;
    data_027e01f8[3] = (void *)&func_01ffe394;
    data_027e01f8[4] = (void *)&func_01ffe3d8;
    data_027e01f8[5] = (void *)&func_01ffe8a0;
    data_027e01f8[6] = (void *)&func_01ffe934;
    data_027e01f8[7] = (void *)&NNSi_G3dFuncSbc_BB;
    data_027e01f8[8] = (void *)&NNSi_G3dFuncSbc_RollBB;
    data_027e01f8[9] = (void *)&func_01ffec28;
    data_027e01f8[10] = (void *)&Sbc_CallDl;
    data_027e01f8[11] = (void *)&func_01fff374;
    data_027e01f8[12] = (void *)&NNSi_G3dFuncSbc_ENVMAP;
    data_027e01f8[13] = (void *)&NNSi_G3dFuncSbc_PRJMAP;
    func_01ffa1f4(1);
}
