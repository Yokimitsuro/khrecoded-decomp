void func_0202d460(int *bits, int n) {
    int i = n / 32;
    n = 31 - (n & 0x1f);
    bits[i] |= 1 << n;
}
