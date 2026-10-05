typedef unsigned int u32;
u32 GetMainBg3Priority(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x400000eU;
    u32 value1 = *(const unsigned short *)(value0);
    u32 value2 = 0x3U;
    u32 value3 = (value2) & (value1);
    return value3;
}
