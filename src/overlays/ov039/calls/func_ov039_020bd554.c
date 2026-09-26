extern int func_ov039_020bcdb8(void *method, int arg);
extern int data_ov039_020beaa4[];
struct ov008_disp { char *obj; int _pad; };
extern struct ov008_disp data_ov039_020be950[];
extern struct ov008_disp data_ov039_020be8f0[];

int func_ov039_020bd554(int param_1, int param_2) {
    int r = 0;
    void *m1 = *(void **)(data_ov039_020be950[data_ov039_020beaa4[0]].obj + 0x3c);
    if (param_1 != 0) {
        r = func_ov039_020bcdb8(m1, param_1);
    }
    if (r == 0) {
        void *m2 = *(void **)(data_ov039_020be8f0[data_ov039_020beaa4[1]].obj + 0x38);
        if (param_2 != 0) {
            r = func_ov039_020bcdb8(m2, param_2);
        }
    }
    return r;
}
