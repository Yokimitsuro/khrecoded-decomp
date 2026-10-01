typedef unsigned int u32;
typedef int BOOL;

extern void FSi_InitRomArchive(u32 defaultDmaNo);
extern void FSi_InitOverlay(void);

BOOL fsi_is_init;

void FS_Init(u32 defaultDmaNo)
{
    if (!fsi_is_init) {
        fsi_is_init = 1;
        FSi_InitRomArchive(defaultDmaNo);
        FSi_InitOverlay();
    }
}