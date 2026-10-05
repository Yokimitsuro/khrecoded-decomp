#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x17];
    u8 nodeCount;
    u8 pad_18[0x28];
    u8 nodeDict[1];
} ModelResource;

typedef struct {
    u8 pad_000[0x24];
    ModelResource *model;
    u8 pad_028[0x2c];
    void *activeNodes;
    u8 pad_058[0xac];
    void *nodes;
    int rootNode;
    int animId;
    int frame;
    int playing;
    u8 pad_118[0x20];
} AnimState;

typedef struct {
    u8 kind;
    u8 pad_001[0x3a3];
    AnimState *anim;
} AnimActor;

extern char sOv041_RpgPlSoTgPZ_020cfa64[];
extern char sOv041_RpgPlHeTgPZ_020cfa78[];
extern char sOv041_RpgPlClTgPZ_020cfa8c[];
extern char sOv041_RpgEn03PZ_020cfaa0[];
extern char sOv041_RpgEn16PZ_020cfab0[];
extern char sOv041_TraTg_020cf710[];
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitSharedRecordAndDispatch(void *state, const char *path, int a, int b);
extern int NNS_G3dGetResDictIdxByName(void *dict, const char *name);

void LoadActorAnimation(AnimActor *actor) {
    char path[20];
    AnimState *anim;
    void *dict;
    int rootNode;

    switch (actor->kind) {
    case 0xff:
        OS_SPrintf(path, sOv041_RpgPlSoTgPZ_020cfa64);
        break;
    case 0xfe:
        OS_SPrintf(path, sOv041_RpgPlHeTgPZ_020cfa78);
        break;
    case 0xfd:
        OS_SPrintf(path, sOv041_RpgPlClTgPZ_020cfa8c);
        break;
    case 3:
        OS_SPrintf(path, sOv041_RpgEn03PZ_020cfaa0);
        break;
    case 0x10:
        OS_SPrintf(path, sOv041_RpgEn16PZ_020cfab0);
        break;
    default:
        return;
    }
    anim = NNSi_FndAllocFromDefaultHeap(sizeof(AnimState));
    actor->anim = anim;
    InitSharedRecordAndDispatch(anim, path, 1, 0x12);
    anim->nodes = NNSi_FndAllocFromDefaultHeap(anim->model->nodeCount * 0x58);
    anim->activeNodes = anim->nodes;
    if (anim->model != NULL) {
        dict = anim->model->nodeDict;
    } else {
        dict = NULL;
    }
    if (dict != NULL) {
        rootNode = NNS_G3dGetResDictIdxByName(dict, sOv041_TraTg_020cf710);
    } else {
        rootNode = -1;
    }
    anim->rootNode = rootNode;
    anim->playing = 0;
    anim->animId = -1;
}
