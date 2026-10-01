void OS_SetArenaLo(int arena, void *value)
{
    *(void **)(0x02fff000 + (arena << 2) + 3488) = value;
}