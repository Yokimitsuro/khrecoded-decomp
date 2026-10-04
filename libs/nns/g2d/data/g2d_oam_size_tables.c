typedef unsigned short u16;

/* OBJ dimensions indexed by [shape][size]. */
const u16 NNSi_objSizeHTbl[3][4] = {
    {  8, 16, 32, 64 },
    {  8,  8, 16, 32 },
    { 16, 32, 32, 64 }
};

const u16 NNSi_objSizeWTbl[3][4] = {
    {  8, 16, 32, 64 },
    { 16, 32, 32, 64 },
    {  8,  8, 16, 32 }
};
