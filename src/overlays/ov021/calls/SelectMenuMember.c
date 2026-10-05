#include "nitro/types.h"

typedef struct MenuMember MenuMember;
typedef struct MemberList MemberList;

typedef struct {
    s32 id;
} MenuCommand;

struct MenuMember {
    s32 id;
    s32 category;
    u32 label;
    u8 pad_0c[0x2c];
    s32 (*handler)(MemberList *list, MenuMember *member, MenuCommand *command);
};

struct MemberList {
    MenuMember **members;
    s32 count;
    MenuMember *current;
    u8 pad_0c[8];
    s32 player;
};

extern int FindCurrentMemberIndex(MemberList *list);
extern u8 *GetBoundedEntryField(int player);
extern void func_ov021_020a7fc0(void *obj, u32 value);
extern void func_ov001_02063a80(int index, int amount);
extern s32 func_ov001_02063a38(void);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void func_ov001_0206df78(void);
extern s32 func_ov001_02078494(void);
extern void func_ov001_02078360(int a, int b);
extern void func_ov001_02078000(int listKind, int entryId);
extern BOOL func_ov001_02077d64(void);

s32 SelectMenuMember(MemberList *list, int index, MenuCommand *command)
{
    MenuMember *member;
    int counter;
    s32 result;

    if (index >= list->count) {
        return 0;
    }
    if (index >= 0) {
        u8 *entry = GetBoundedEntryField(list->player);
        list->current = list->members[index];
        if (list->current != NULL) {
            func_ov021_020a7fc0(entry + 0xb2c, list->current->label);
        }
    } else {
        index = FindCurrentMemberIndex(list);
    }
    member = list->current;
    counter = -1;
    switch (member->category) {
    case 1:
        switch (member->id) {
        case 0xb7:
        case 0xb8:
        case 0xbb:
        case 0xbc:
        case 0xbd:
            counter = 5;
            break;
        }
        break;
    case 2:
        counter = 4;
        switch (member->id) {
        case 0xa0:
        case 0xa1:
        case 0xa2:
        case 0xb1:
            func_ov001_02063a80(5, 1);
            break;
        }
        if (func_ov001_02063a38() != 4) {
            u32 total = ReadSessionPackedBits(0xb15, 0x11);
            if (total < 99999) {
                total++;
            }
            WriteSessionPackedBits(0xb15, 0x11, total);
        }
        break;
    case 3:
        counter = 3;
        break;
    case 4:
        func_ov001_0206df78();
        break;
    }
    if (counter >= 0) {
        func_ov001_02063a80(counter, 1);
    }
    result = list->current->handler(list, list->current, command);
    if (member->category != 1 && member->category != 4 && command->id != 0x1c) {
        if (func_ov001_02078494() == 2) {
            func_ov001_02078360(0, 1);
        }
        func_ov001_02078000(func_ov001_02078494(), index);
        func_ov001_02077d64();
    }
    return result;
}
