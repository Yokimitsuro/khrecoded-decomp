extern int func_ov003_02064c10(int stream);
extern int data_ov003_020658c4[];

void updateMovieStreamLeadTime(int stream) {
    int lead;

    switch (*(int *)(stream + 0x64)) {
    case 0:
        *(int *)(stream + 0x4c) = 0;
        break;
    case 1:
        if (*(int *)(stream + 0x50) == 0) {
            lead = (*(int *)(stream + 0x34) - func_ov003_02064c10(stream)) / 2;
            *(int *)(stream + 0x4c) = lead;
            if (lead < 0) {
                *(int *)(stream + 0x4c) = 0;
            }
            data_ov003_020658c4[0] = *(int *)(stream + 0x4c);
        } else {
            *(int *)(stream + 0x4c) = data_ov003_020658c4[0];
        }
        break;
    case 2:
        *(int *)(stream + 0x4c) = *(int *)(stream + 0x34) - func_ov003_02064c10(stream);
        break;
    }
}
