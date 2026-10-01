void *OS_GetArenaLo(int arena)
{
    return *(void **)(0x02fff000 + (arena << 2) + 3488);
}