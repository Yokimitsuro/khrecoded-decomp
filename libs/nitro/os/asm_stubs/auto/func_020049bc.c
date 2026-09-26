asm void func_020049bc(register unsigned int cycles)
{
loop:
    subs r0, r0, #4
    bhs loop
    bx lr
}
