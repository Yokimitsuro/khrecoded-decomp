struct ov008_ptr_slot {
    char *ptr;
    int _pad;
};

extern int data_ov039_020beaa4[];
extern struct ov008_ptr_slot data_ov039_020be950[];
int func_ov039_020bd654(void)
{
    return *(int *)(data_ov039_020be950[data_ov039_020beaa4[0]].ptr + 0xc);
}
