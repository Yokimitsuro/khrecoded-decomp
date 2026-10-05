extern char gBgLayerTransferDispatch[];

void Callbacks_RunTableEntry(int index, int arg1, int arg2, int arg3) {
    void (*callback)(int arg1, int arg2, int arg3);

    callback = *(void (**)(int, int, int))(gBgLayerTransferDispatch + index * 0x18);
    if (callback != 0) {
        callback(arg1, arg2, arg3);
    }
}
