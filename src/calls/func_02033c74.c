extern void UnlinkNodeFromList(int);

void func_02033c74(int *param_1, int param_2) {
    if (param_1[0x27] == 0) {
        return;
    }
    UnlinkNodeFromList(param_2);
}
