typedef struct {
    char pad0[0xc];
    unsigned long long seed;
    unsigned long long multiplier;
    unsigned long long increment;
} RandomGeneratorState;

extern RandomGeneratorState data_020604d8;

int nextRandom12(void)
{
    RandomGeneratorState *state = &data_020604d8;
    unsigned int newSeedHighWord;

    state->seed = state->multiplier * state->seed + state->increment;
    newSeedHighWord = (unsigned int)(state->seed >> 32);
    return (int)(((unsigned long long)newSeedHighWord << 12) >> 32);
}
