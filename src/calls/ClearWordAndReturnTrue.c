typedef unsigned int u32;
u32 ClearWordAndReturnTrue(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x0U;
    *(u32 *)(argument0) = value0;
    u32 value2 = 0x1U;
    return value2;
}
