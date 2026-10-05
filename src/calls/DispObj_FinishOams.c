#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef union GXOamAttr {
    struct {
        u32 attr01;
        u16 attr2;
        u16 _3;
    };
    struct {
        u32 y : 8;
        u32 rsMode : 2;
        u32 objMode : 2;
        u32 mosaic : 1;
        u32 colorMode : 1;
        u32 shape : 2;
        u32 x : 9;
        u32 rsParam : 5;
        u32 size : 2;
        u32 charNo : 10;
        u32 priority : 2;
        u32 cParam : 4;
        u32 attr3 : 16;
    };
} GXOamAttr;

typedef enum {
    GX_OAM_MODE_NORMAL = 0,
    GX_OAM_MODE_XLU = 1,
    GX_OAM_MODE_OBJWND = 2,
    GX_OAM_MODE_BITMAPOBJ = 3
} GXOamMode;

#define GX_OAM_ATTR01_MODE_SHIFT 10
#define GX_OAM_ATTR01_MODE_MASK 0x00000c00
#define GX_OAM_ATTR2_NAME_MASK 0x03ff
#define GX_OAM_ATTR2_PRIORITY_SHIFT 10
#define GX_OAM_ATTR2_PRIORITY_MASK 0x0c00
#define GX_OAM_ATTR2_CPARAM_SHIFT 12
#define GX_OAM_ATTR2_CPARAM_MASK 0xf000

static inline GXOamMode G2_GetOBJMode(const GXOamAttr *oam)
{
    return (GXOamMode)((oam->attr01 & GX_OAM_ATTR01_MODE_MASK) >> GX_OAM_ATTR01_MODE_SHIFT);
}

static inline void G2_SetOBJMode(GXOamAttr *oam, GXOamMode mode, int cParam)
{
    oam->attr01 = (oam->attr01 & ~GX_OAM_ATTR01_MODE_MASK) | (mode << GX_OAM_ATTR01_MODE_SHIFT);
    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_CPARAM_MASK) | (cParam << GX_OAM_ATTR2_CPARAM_SHIFT));
}

static inline int G2_GetOBJCharName(const GXOamAttr *oam)
{
    return oam->attr2 & GX_OAM_ATTR2_NAME_MASK;
}

static inline void G2_SetOBJCharName(GXOamAttr *oam, int name)
{
    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_NAME_MASK) | name);
}

static inline void G2_SetOBJPriority(GXOamAttr *oam, int priority)
{
    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_PRIORITY_MASK) | (priority << GX_OAM_ATTR2_PRIORITY_SHIFT));
}

typedef struct {
    u8 pad_00[0x5c];
    int charNameOffset;
} DispObjElement;

struct DispObjFlags { unsigned int unk_bit0 : 1, unk_bit1 : 1, unk_bit2 : 1, translucent : 1; };

typedef struct DispObj {
    char pad00[0xc];
    fx32 x;
    fx32 y;
    char pad14[0x6c - 0x14];
    int palette;
    int priority;
    int elementIndex;
    struct DispObjFlags flags;
} DispObj;

extern DispObjElement *GetElementAddress(void *base, int index);
extern void DispObj_MirrorOam(DispObj *owner, GXOamAttr *oam, int rsParam);
extern void PushQueueEntry(void *base, GXOamAttr *oam, int affineIndex);

void DispObj_FinishOams(void *base, DispObj *obj, GXOamAttr *oams, int count, int affineIndex)
{
    int i;
    int screenY = obj->y >> 12;
    int charNameOffset = GetElementAddress(base, obj->elementIndex)->charNameOffset;
    GXOamMode blendMode = obj->flags.translucent ? GX_OAM_MODE_XLU : GX_OAM_MODE_NORMAL;

    for (i = 0; i < count; i++, oams++) {
        int oamY = ((int)oams->y + 0x40) % 256 - 0x40;
        GXOamMode mode;

        if (screenY <= -0xc0 || screenY > 0x140) {
            continue;
        }
        if (screenY < 0x40 && oamY > screenY + 0x80) {
            continue;
        }
        if (screenY > 0x40 && oamY < screenY - 0x80) {
            continue;
        }
        G2_SetOBJCharName(oams, charNameOffset + G2_GetOBJCharName(oams));
        switch (G2_GetOBJMode(oams)) {
        case GX_OAM_MODE_OBJWND:
            mode = GX_OAM_MODE_OBJWND;
            break;
        case GX_OAM_MODE_BITMAPOBJ:
            mode = GX_OAM_MODE_BITMAPOBJ;
            break;
        default:
            mode = blendMode;
            break;
        }
        if (obj->palette != -1) {
            G2_SetOBJMode(oams, mode, obj->palette);
        } else {
            G2_SetOBJMode(oams, mode, oams->cParam);
        }
        DispObj_MirrorOam(obj, oams, affineIndex);
        G2_SetOBJPriority(oams, obj->priority);
        PushQueueEntry(base, oams, affineIndex);
    }
}
