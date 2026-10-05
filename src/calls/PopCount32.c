typedef unsigned int u32;
u32 PopCount32(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = 0x55555555U;
    u32 value1 = 0x33333333U;
    u32 value2 = (value0) & (((argument0) >> 1));
    u32 value3 = (argument0) - (value2);
    u32 value4 = (value3) & (value1);
    u32 value5 = (value1) & (((value3) >> 2));
    u32 value6 = (value4) + (value5);
    u32 value7 = 0xf0f0f0fU;
    u32 value8 = (value6) + (((value6) >> 4));
    u32 value9 = (value8) & (value7);
    u32 value10 = (value9) + (((value9) >> 8));
    u32 value11 = (value10) + (((value10) >> 16));
    u32 value12 = (value11) & (0xffU);
    return value12;
}
