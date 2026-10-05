typedef unsigned int u32;
u32 ReadHalfword(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)(argument0);
    return value0;
}
