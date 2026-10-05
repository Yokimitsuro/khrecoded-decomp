extern void camera_commit_projection(int x);
extern int func_ov044_020d0bd8(void);

int func_ov044_020d00a0(int x) {
    camera_commit_projection(x);
    return func_ov044_020d0bd8();
}
