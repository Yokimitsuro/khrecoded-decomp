extern void func_ov022_020a9334(void *sub);
void func_ov022_020a809c(char *node) {
    func_ov022_020a9334(*(void **)node);
    *(int *)(node + 0x40) += 1;
}
