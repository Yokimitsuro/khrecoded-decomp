typedef struct NNSFndAllocator NNSFndAllocator;
typedef struct NNSG3dAnmObj NNSG3dAnmObj;

extern void NNS_FndFreeToAllocator(NNSFndAllocator *allocator, void *memBlock);

void NNS_G3dFreeAnmObj(NNSFndAllocator *allocator, NNSG3dAnmObj *anmObj)
{
    NNS_FndFreeToAllocator(allocator, anmObj);
}
