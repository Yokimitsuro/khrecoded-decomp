extern void NNS_G3dGeBufferOP_N(unsigned int nCmd, const void *pSrc,
                          unsigned int nWords);

#define PACK(v) ((unsigned int)(unsigned short)((v) << 22 >> 16))

void DrawFlatRect(int nX0, int nY0, int nX1, int nY1, int nZ)
{
    unsigned int nAttr;
    unsigned int nColour;
    unsigned int nBegin;
    unsigned int nVtxA[2];
    unsigned int nVtxB[2];
    unsigned int nVtxC[2];
    unsigned int nVtxD[2];

    nAttr = 0x1f00c0;
    NNS_G3dGeBufferOP_N(0x29, &nAttr, 1);
    nColour = 0;
    NNS_G3dGeBufferOP_N(0x20, &nColour, 1);
    nBegin = 1;
    NNS_G3dGeBufferOP_N(0x40, &nBegin, 1);

    nVtxA[0] = PACK(nX0) | PACK(nY0) << 16;
    nVtxA[1] = PACK(nZ);
    NNS_G3dGeBufferOP_N(0x23, nVtxA, 2);

    nVtxB[0] = PACK(nX1) | PACK(nY0) << 16;
    nVtxB[1] = PACK(nZ);
    NNS_G3dGeBufferOP_N(0x23, nVtxB, 2);

    nVtxC[0] = PACK(nX1) | PACK(nY1) << 16;
    nVtxC[1] = PACK(nZ);
    NNS_G3dGeBufferOP_N(0x23, nVtxC, 2);

    nVtxD[0] = PACK(nX0) | PACK(nY1) << 16;
    nVtxD[1] = PACK(nZ);
    NNS_G3dGeBufferOP_N(0x23, nVtxD, 2);

    NNS_G3dGeBufferOP_N(0x41, 0, 0);
}
