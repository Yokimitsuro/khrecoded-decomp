/* Retries the PXI send on channel 0xc until the FIFO accepts it. */
extern int func_0200e320(int channel, int data, int flag);

void OSi_SendToPxi(int data) {
    int payload = data << 8;
    int channel = 0xc;
    int zero = 0;
    while (func_0200e320(channel, payload, zero) != 0) {
        ;
    }
}
