typedef unsigned int u32;
u32 Obj_SetWord2C(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    *(u32 *)((argument0 + 0x2cU)) = argument1;
    return argument0;
}
