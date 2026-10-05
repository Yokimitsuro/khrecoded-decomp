typedef unsigned int u32;
u32 SwapWord32(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)(argument0);
    u32 value1 = *(const u32 *)(argument1);
    *(u32 *)(argument0) = value1;
    *(u32 *)(argument1) = value0;
    return argument0;
}
