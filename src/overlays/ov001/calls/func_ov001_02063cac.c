extern int func_ov001_0206685c(void);
extern int func_ov021_020af830(void);

int func_ov001_02063cac(void) {
    if (func_ov001_0206685c() != 0) {
        return 1;
    }
    return func_ov021_020af830() != 0;
}
