extern void camera_commit_projection(int x);
extern int UpdatePanelViewAxes(void);

int func_ov044_020d00a0(int x) {
    camera_commit_projection(x);
    return UpdatePanelViewAxes();
}
