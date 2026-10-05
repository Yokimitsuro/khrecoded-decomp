extern int func_ov022_020a8d00(int stream);
extern int data_ov022_020b7e10[];

void updateMovieStreamLeadTime_020a8f1c(int stream) {
    int lead;

    switch (*(int *)(stream + 0x64)) {
    case 0:
        *(int *)(stream + 0x4c) = 0;
        break;
    case 1:
        if (*(int *)(stream + 0x50) == 0) {
            lead = (*(int *)(stream + 0x34) - func_ov022_020a8d00(stream)) / 2;
            *(int *)(stream + 0x4c) = lead;
            if (lead < 0) {
                *(int *)(stream + 0x4c) = 0;
            }
            data_ov022_020b7e10[0] = *(int *)(stream + 0x4c);
        } else {
            *(int *)(stream + 0x4c) = data_ov022_020b7e10[0];
        }
        break;
    case 2:
        *(int *)(stream + 0x4c) = *(int *)(stream + 0x34) - func_ov022_020a8d00(stream);
        break;
    }
}
