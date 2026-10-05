typedef unsigned int u32;
u32 Obj_SetWord14(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    *(u32 *)((argument0 + 0x14U)) = argument1;
    return argument0;
}
