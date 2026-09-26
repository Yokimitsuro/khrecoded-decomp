extern struct { int a, b; } data_0205d894;

void SND_ClearChannelBit(int bit) {
    data_0205d894.b &= ~(1 << bit);
}
