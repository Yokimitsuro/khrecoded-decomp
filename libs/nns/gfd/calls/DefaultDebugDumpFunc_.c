typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSiGfdDefaultDebugContext {
    u32 totalFree;
    u32 totalReserved;
} NNSiGfdDefaultDebugContext;

void DefaultDebugDumpFunc_(int index, u32 startAddress, u32 endAddress, u32 blockMax, BOOL active, void *userContext)
{
#pragma unused(index)
    NNSiGfdDefaultDebugContext *context = (NNSiGfdDefaultDebugContext *)userContext;

    if (active) {
        context->totalFree += endAddress - startAddress;
        context->totalReserved += blockMax;
    }
}