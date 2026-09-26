extern void func_02018864(int *ptr, int arg);
extern void func_02018770(void *pRenderObj, void *pAnmObj);

typedef struct {
    short field_00;
    short blend[5];
    void *boundAnm[5];
} AnimState;

typedef struct {
    short numBlends[5];
    char pad_0a[0x10 - 0xa];
    void **blendAnms[5];
} BlendTable;

void func_0202f2e0(AnimState *anim, unsigned short nTrack, BlendTable *table, short nBlend)
{
    if (table->numBlends[nTrack] == 0)
        return;

    void *cur = anim->boundAnm[nTrack];
    void *target = table->blendAnms[nTrack][nBlend];
    if (cur == target)
        return;

    if (cur != 0)
        func_02018864((int *)((char *)anim + 0x20), (int)cur);

    anim->blend[nTrack] = nBlend;
    if (nBlend >= 0) {
        target = table->blendAnms[nTrack][nBlend];
        anim->boundAnm[nTrack] = target;
        func_02018770((char *)anim + 0x20, target);

        *(int *)((char *)anim->boundAnm[nTrack] + 4) = 0x1000;
        *(int *)anim->boundAnm[nTrack] = 0;
        return;
    }
    anim->boundAnm[nTrack] = 0;
}
