extern int func_0202a45c(void *classDesc, int *params);

extern int data_ov001_0209ead0;
extern char data_ov001_0209ead4[];

void func_ov001_02068d5c(int param) {
    int params[1];

    params[0] = param;
    data_ov001_0209ead0 = func_0202a45c(data_ov001_0209ead4, params);
}
