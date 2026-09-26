int func_0202d4b4(int *bits, int n) {
    int i = n / 32;
    n = 31 - (n & 0x1f);
    return bits[i] & (1 << n);
}
