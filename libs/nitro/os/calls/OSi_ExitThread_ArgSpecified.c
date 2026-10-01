typedef unsigned int u32;

typedef struct OSContext {
    u32 cpsr;
    u32 registers[1];
    unsigned char padding08[0x5c];
} OSContext;

typedef struct OSThread {
    OSContext context;
    int state;
} OSThread;

typedef struct OSThreadSystem {
    unsigned char padding00[0x14];
    void *destructorStack;
} OSThreadSystem;

extern OSThreadSystem data_02056b50;
extern void OS_InitContext(OSContext *context, u32 entryPoint, u32 stackPointer);
extern void OS_LoadContext(OSContext *context);
extern void OSi_ExitThread(void *argument);

asm void OSi_ExitThread_ArgSpecified(OSThread *thread, void *argument)
{
    stmfd sp!, {r3, r4, r5, lr}
    ldr r2, =data_02056b50
    mov r5, r0
    ldr r2, [r2, #0x14]
    mov r4, r1
    cmp r2, #0
    beq noDestructorStack
    ldr r1, =OSi_ExitThread
    bl OS_InitContext
    ldr r0, [r5]
    mov r1, #1
    orr r2, r0, #0x80
    stmia r5, {r2, r4}
    mov r0, r5
    str r1, [r5, #0x64]
    bl OS_LoadContext
    ldmfd sp!, {r3, r4, r5, pc}
noDestructorStack:
    mov r0, r4
    bl OSi_ExitThread
    ldmfd sp!, {r3, r4, r5, pc}
}