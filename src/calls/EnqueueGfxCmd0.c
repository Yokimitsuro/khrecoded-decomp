extern int NNS_GfdRegisterNewVramTransferTask();

int EnqueueGfxCmd0(int arg0, int arg1, int arg2) {
    return NNS_GfdRegisterNewVramTransferTask(0, arg1, arg0, arg2);
}
