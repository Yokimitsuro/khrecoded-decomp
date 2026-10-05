typedef unsigned int u32;
u32 CopyTransformFields(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    *(u32 *)((argument0 + 0x14U)) = argument1;
    u32 value1 = *(const u32 *)((argument1 + 0x18U));
    *(u32 *)((argument0 + 0x18U)) = value1;
    u32 value3 = *(const u32 *)((argument1 + 0x1cU));
    *(u32 *)((argument0 + 0x1cU)) = value3;
    u32 value5 = *(const u32 *)((argument1 + 0x20U));
    *(u32 *)((argument0 + 0x20U)) = value5;
    u32 value7 = *(const short *)((argument1 + 0x26U));
    *(u32 *)((argument0 + 0x30U)) = value7;
    u32 value9 = *(const short *)((argument1 + 0x28U));
    *(u32 *)((argument0 + 0x34U)) = value9;
    u32 value11 = *(const short *)((argument1 + 0x2aU));
    *(u32 *)((argument0 + 0x38U)) = value11;
    return argument0;
}
