int PrintfDest_PutChar(int *arg0, char arg1) {
    if (arg0[0] != 0) {
        *(char *)arg0[1] = arg1;
        arg0[0] -= 1;
    }
    arg0[1] += 1;
}
