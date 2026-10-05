typedef struct {
    char pad0[0xc];
    long long seed;
    long long mult;
    long long inc;
} RngState;

extern RngState data_020604d8;

unsigned int random_next_scaled(unsigned int upperBound)
{
    RngState *randomState = &data_020604d8;
    unsigned int randomValue;

    randomState->seed = randomState->mult * randomState->seed + randomState->inc;
    randomValue = (unsigned int)(randomState->seed >> 32);
    if (upperBound != 0)
        randomValue = (unsigned int)((unsigned long long)randomValue * upperBound >> 32);
    return randomValue;
}
