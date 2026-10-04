typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSiGfdDefaultDebugContext {
    u32 totalFree;
    u32 totalReserved;
} NNSiGfdDefaultDebugContext;

typedef void (*NNSGfdFrmTexVramDebugDumpCallBack)(int, u32, u32, u32, BOOL, void *);

extern void DefaultDebugDumpFunc_(int, u32, u32, u32, BOOL, void *);
extern void NNS_GfdDumpFrmTexVramManagerEx(NNSGfdFrmTexVramDebugDumpCallBack callback, void *userContext);

void NNS_GfdDumpFrmTexVramManager(void)
{
    NNSiGfdDefaultDebugContext context = { 0, 0 };

    NNS_GfdDumpFrmTexVramManagerEx(DefaultDebugDumpFunc_, &context);
}