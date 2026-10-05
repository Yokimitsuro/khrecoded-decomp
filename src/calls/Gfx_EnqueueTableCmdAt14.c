extern int NNS_GfdRegisterNewVramTransferTask(void *a, int b, int c, int d);
extern void *data_02055738[];

int Gfx_EnqueueTableCmdAt14(int idx, void *p, int arg2, int arg3) {
    return NNS_GfdRegisterNewVramTransferTask(data_02055738[idx], arg2, *(int *)((char *)p + 0x14), arg3);
}
