typedef unsigned int u32;
u32 StoreWord0(u32 argument0, u32 argument1, u32 argument2, u32 argument3) {
    *(u32 *)(argument0) = argument1;
    return argument0;
}
