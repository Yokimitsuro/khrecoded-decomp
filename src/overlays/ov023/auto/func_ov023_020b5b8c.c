void *func_ov023_020b5b8c(char *node, unsigned short id) {
    char *found = 0;
    int step = *(int *)node;
    if (step != -1) {
        do {
            if (*(unsigned short *)(node + 6) == id) {
                found = node;
                break;
            }
            node += step;
            step = *(int *)node;
        } while (step != -1);
    }
    return found;
}
