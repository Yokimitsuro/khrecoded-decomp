extern int SetSessionStateBit(int a, int b);
int RequestScene11(void) {
    return SetSessionStateBit(1, 0);
}
