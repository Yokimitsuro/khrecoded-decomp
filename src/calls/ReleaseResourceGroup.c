typedef struct {
    int group_tag;
    int reference_count;
    int *section_pointers[8];
} ResourceGroup;

extern void NNS_G3dResDefaultRelease(void *pResData);

void ReleaseResourceGroup(ResourceGroup *group)
{
    int section_index, entry_index;

    if (group->reference_count == 0) {
        return;
    }
    group->reference_count = group->reference_count - 1;
    if (group->reference_count == 0 && group->group_tag == 0x4850414b) {
        for (section_index = 0; section_index < 8; section_index++) {
            if (group->section_pointers[section_index] != 0) {
                entry_index = 0;
                while (entry_index < *(unsigned int *)group->section_pointers[section_index]) {
                    if (section_index == 7) {
                        NNS_G3dResDefaultRelease((void *)group->section_pointers[section_index][entry_index + 1]);
                    }
                    entry_index = entry_index + 1;
                }
            }
        }
    }
}
