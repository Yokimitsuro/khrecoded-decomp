extern void SetSlotAnimSequence(int target, int index, unsigned int value);

struct Ov008SubitemBlock { char pad0[0x14]; int idx[2]; char pad1[0x28]; unsigned int alt[2]; char pad2[8]; unsigned int val[2]; char pad3[0x94-0x5c]; unsigned int bUseAlt:1; };

void ApplySelectedSubitemValues(int target, struct Ov008SubitemBlock *obj, int useAlt) {
    int i = 0;
    do {
        int index = obj->idx[i];
        if (index != -1) {
            if (useAlt != 0) {
                unsigned int v = obj->alt[i];
                if (v != 0xffffffff) SetSlotAnimSequence(target, index, v);
            } else {
                unsigned int v = obj->val[i];
                if (v != 0xffffffff) SetSlotAnimSequence(target, index, v);
            }
        }
        i++;
    } while (i < 2);
    obj->bUseAlt = (useAlt == 0);
}
