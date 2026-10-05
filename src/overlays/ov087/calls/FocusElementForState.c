#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[1];
} EntryList;

extern void *func_ov039_020bc1dc(void);
extern void func_ov087_020c5220(EntryList *list);
extern void *FindWidgetById(void *container, int elementId);
extern void SetFocusedWidget(void *container, void *element);
extern void MoveCursorToWidget(EntryList *list, void *element, int arg2, int arg3);

void FocusElementForState(EntryList *list, int stateId)
{
    void *container = func_ov039_020bc1dc();
    u32 selectedId = list->entries[list->cursor].id;
    int elementId;
    void *element;

    func_ov087_020c5220(list);
    switch (stateId) {
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
        return;
    case 12:
        elementId = 3;
        break;
    case 11:
        switch (selectedId) {
        case 3:
        case 6:
            elementId = 3;
            break;
        case 7:
            elementId = 3;
            break;
        default:
            elementId = 4;
            break;
        }
        break;
    case 10:
    case 14:
        elementId = 2;
        break;
    case 13:
        elementId = 2;
        break;
    case 5:
        elementId = selectedId == 6 ? 2 : 3;
        break;
    default:
        return;
    }
    if (stateId != 0x10 && stateId != 0x11) {
        element = FindWidgetById(container, elementId);
        SetFocusedWidget(container, element);
        MoveCursorToWidget(list, element, 0, 0);
    }
}
