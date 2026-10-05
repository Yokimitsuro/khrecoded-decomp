extern int data_020608c8;
void SetParamWord8(int param_1) {
    *(int *)((char *)&data_020608c8 + 8) = param_1;
}
