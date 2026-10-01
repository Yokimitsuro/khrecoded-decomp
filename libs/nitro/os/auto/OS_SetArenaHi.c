void OS_SetArenaHi(int arena, void *high)
{
    *(void **)(0x02fff000 + (arena << 2) + 3524) = high;
}