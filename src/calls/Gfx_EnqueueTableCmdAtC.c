extern int NNS_GfdRegisterNewVramTransferTask(void *a, int b, int c, int d);
extern void *data_02055758[];

int Gfx_EnqueueTableCmdAtC(int idx, void *p, int arg2, int arg3) {
    return NNS_GfdRegisterNewVramTransferTask(data_02055758[idx], arg2, (int)((char *)p + 0xc), arg3);
}
