extern volatile int data_02057c10;

asm void func_0200e8e0(void)
{
    ldr r12, =data_02057c10
loop:
    ldr r0, [r12, #0]
    cmp r0, #1
    beq loop
    bx lr
}
