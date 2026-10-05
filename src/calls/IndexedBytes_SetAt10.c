typedef unsigned int u32;
u32 IndexedBytes_SetAt10(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = (argument0) + (argument1);
    *(unsigned char *)((value0 + 0x10U)) = argument2;
    return value0;
}
