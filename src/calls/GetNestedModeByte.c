typedef unsigned int u32;
u32 GetNestedModeByte(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    u32 value0 = *(const u32 *)(argument0);
    u32 value1 = *(const u32 *)(value0);
    u32 value2 = *(const u32 *)((value1 + 0x8U));
    u32 value3 = *(const unsigned char *)((value2 + 0x1U));
    return value3;
}
