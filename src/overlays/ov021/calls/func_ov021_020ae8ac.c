extern int func_01ffa0f4(int *a, int *b);
extern void func_01ffb12c(unsigned short *p);

struct vec3_0208ffe8 {
    int a;
    int b;
    int c;
};
extern struct vec3_0208ffe8 data_0205ab3c;

void func_ov021_020ae8ac(unsigned short *param_1, int param_2, int param_3, int param_4) {
    struct vec3_0208ffe8 local_1c;
    struct vec3_0208ffe8 local_28;
    int iVar1;
    int iVar2;
    local_1c = data_0205ab3c;
    local_28 = *(struct vec3_0208ffe8 *)(param_1 + 0x52);
    iVar2 = local_1c.b - local_28.b;
    local_28.b = 0;
    local_1c.b = 0;
    iVar1 = func_01ffa0f4((int *)&local_28, (int *)&local_1c);
    if (iVar1 < 0xccd) {
        if (iVar2 < 0) {
            iVar2 = -iVar2;
        }
        if (iVar2 < 0x8000) {
            return;
        }
    }
    func_01ffb12c(param_1);
}
