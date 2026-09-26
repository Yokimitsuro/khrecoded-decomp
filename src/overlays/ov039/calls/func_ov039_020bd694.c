struct ov008_ptr_slot {
    char *ptr;
    int _pad;
};

extern int data_ov039_020beaa4[];
extern struct ov008_ptr_slot data_ov039_020be8f0[];
int func_ov039_020bd694(void)
{
    return *(int *)(data_ov039_020be8f0[data_ov039_020beaa4[1]].ptr + 0xc);
}
