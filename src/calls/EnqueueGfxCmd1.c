extern int NNS_GfdRegisterNewVramTransferTask();

int EnqueueGfxCmd1(int arg0, int arg1, int arg2) {
    return NNS_GfdRegisterNewVramTransferTask(1, arg1, arg0, arg2);
}
