extern volatile int data_027e00ac;

void FSi_WaitForCardThread(int unused) {
    (void)unused;
    while (data_027e00ac != 0) {}
}
