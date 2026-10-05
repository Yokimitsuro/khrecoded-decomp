typedef unsigned int u32;
u32 Flags16_SetBit1(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const unsigned short *)(argument0);
    u32 value1 = (value0) | (0x2U);
    *(unsigned short *)(argument0) = value1;
    return argument0;
}
