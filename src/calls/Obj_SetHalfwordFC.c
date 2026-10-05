typedef unsigned int u32;
u32 Obj_SetHalfwordFC(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    *(unsigned short *)((argument0 + 0xfcU)) = argument1;
    return argument0;
}
