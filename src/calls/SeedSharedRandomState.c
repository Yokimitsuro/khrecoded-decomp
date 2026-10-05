extern int data_020604d8[];

void SeedSharedRandomState(int seed_word_0, int seed_word_1, int seed_word_2) {
    data_020604d8[3] = seed_word_1;
    data_020604d8[4] = seed_word_2;
    data_020604d8[5] = 0x6c078965;
    data_020604d8[6] = 0x5d588b65;
    data_020604d8[7] = 0x269ec3;
    data_020604d8[8] = 0;
    data_020604d8[0] = seed_word_0;
    data_020604d8[1] = 0x5d588b65;
    data_020604d8[2] = 0x269ec3;
}
