extern int data_ov025_020b7780;
extern int ApplyModeAndNotify();

int LookupChannelEntry_020b62ac(int arg0) {
    return ApplyModeAndNotify(*(int *)&data_ov025_020b7780 + 25844, arg0);
}
