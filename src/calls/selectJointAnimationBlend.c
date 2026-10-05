extern void NNS_G3dRenderObjRemoveAnmObj(int *ptr, int arg);
extern void NNS_G3dRenderObjAddAnmObj(void *pRenderObj, void *pAnmObj);

typedef struct {
    short field_00;
    short selectedAnimationIndices[5];
    void *boundAnimations[5];
} AnimationBindingState;

typedef struct {
    short animationCounts[5];
    char pad_0a[0x10 - 0xa];
    void **animationChoices[5];
} AnimationBlendTable;

void selectJointAnimationBlend(AnimationBindingState *animationState, unsigned short trackIndex, AnimationBlendTable *blendTable, short blendIndex)
{
    if (blendTable->animationCounts[trackIndex] == 0)
        return;

    void *currentAnimation = animationState->boundAnimations[trackIndex];
    void *targetAnimation = blendTable->animationChoices[trackIndex][blendIndex];
    if (currentAnimation == targetAnimation)
        return;

    if (currentAnimation != 0)
        NNS_G3dRenderObjRemoveAnmObj((int *)((char *)animationState + 0x20), (int)currentAnimation);

    animationState->selectedAnimationIndices[trackIndex] = blendIndex;
    if (blendIndex >= 0) {
        targetAnimation = blendTable->animationChoices[trackIndex][blendIndex];
        animationState->boundAnimations[trackIndex] = targetAnimation;
        NNS_G3dRenderObjAddAnmObj((char *)animationState + 0x20, targetAnimation);

        *(int *)((char *)animationState->boundAnimations[trackIndex] + 4) = 0x1000;
        *(int *)animationState->boundAnimations[trackIndex] = 0;
        return;
    }
    animationState->boundAnimations[trackIndex] = 0;
}
