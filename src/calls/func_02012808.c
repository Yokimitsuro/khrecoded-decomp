extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void func_02002abc(void *queue);
extern void func_0200299c(void);
extern char data_0205a488;

typedef struct {
    int (*run)(void *);
    void (*done)(void *);
    int result;
    int rest[6];
} Ov_CardJob;

void func_02012808(char *ctx) {
    Ov_CardJob job;
    void (*done)(void *);
    int enabled;
    for (;;) {
        MI_CpuFill8(&job, 0, 0x24);
        enabled = OS_DisableInterrupts();
        while (*(char *volatile *)(ctx + 0xc0) == 0) {
            func_02002abc(0);
        }
        job = *(Ov_CardJob *)*(char *volatile *)(ctx + 0xc0);
        OS_RestoreInterrupts(enabled);
        if (job.run != 0) {
            job.result = job.run(&job);
        }
        enabled = OS_DisableInterrupts();
        done = job.done;
        *((char *)&data_0205a488 + 0x26) = 0;
        if (done != 0) {
            done(&job);
        }
        if (*(int *)&data_0205a488 != 0) {
            *(char *volatile *)(ctx + 0xc0) = 0;
            OS_RestoreInterrupts(enabled);
        } else {
            func_0200299c();
            return;
        }
    }
}
