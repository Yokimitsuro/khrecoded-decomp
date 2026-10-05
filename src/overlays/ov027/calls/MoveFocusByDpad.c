#include "nitro/types.h"

typedef struct FocusFlags {
    unsigned disabled : 1;
    unsigned focusable : 1;
    unsigned unk_2 : 2;
    unsigned gatedUp : 1;
    unsigned gatedDown : 1;
    unsigned gatedLeft : 1;
    unsigned gatedRight : 1;
} FocusFlags;

typedef struct FocusNode {
    u8 pad_00[0xC];
    int groupId;
    u8 pad_10[0x84];
    FocusFlags flags;
    struct FocusNode *up;
    struct FocusNode *down;
    struct FocusNode *left;
    struct FocusNode *right;
    void (*onConfirm)(struct FocusNode *node);
} FocusNode;

typedef struct FocusRoot {
    u8 pad_00[0x644C];
    void (*onInput)(FocusNode *node, int keys);
    u8 pad_6450[0x1C];
    FocusNode *focused;
    u8 pad_6470[0x4];
    u16 allowedDirs;
} FocusRoot;

extern u16 data_020604fc;
extern u16 data_02060500;
extern void SetFocusedWidget(FocusRoot *root, FocusNode *node);

void MoveFocusByDpad(FocusRoot *root, int keys) {
    FocusNode *cur;
    FocusNode *next;
    u16 dirs;
    u16 newDir;
    void (*confirm)(FocusNode *node);

    cur = root->focused;
    if (cur == NULL) {
        return;
    }
    if ((data_020604fc & root->allowedDirs) == 0) {
        root->allowedDirs = 0xF0;
    }
    dirs = root->allowedDirs;

    /* gated links need the direction key held */
    if ((keys & 0x40) & dirs) {
        next = cur->up;
        if (next != NULL) {
            do {
                if (cur->flags.gatedUp == 1 && (data_02060500 & 0x40) == 0) {
                    break;
                }
                if (next->groupId == cur->groupId || next->groupId == root->focused->groupId) {
                    break;
                }
                if (!next->flags.disabled && next->flags.focusable) {
                    SetFocusedWidget(root, next);
                    newDir = 0x40;
                    goto store_dir;
                }
                cur = next;
                next = next->up;
            } while (next != NULL);
        }
    } else if ((keys & 0x80) & dirs) {
        next = cur->down;
        if (next != NULL) {
            do {
                if (cur->flags.gatedDown == 1 && (data_02060500 & 0x80) == 0) {
                    break;
                }
                if (next->groupId == cur->groupId || next->groupId == root->focused->groupId) {
                    break;
                }
                if (!next->flags.disabled && next->flags.focusable) {
                    SetFocusedWidget(root, next);
                    newDir = 0x80;
                    goto store_dir;
                }
                cur = next;
                next = next->down;
            } while (next != NULL);
        }
    } else if ((keys & 0x20) & dirs) {
        next = cur->left;
        if (next != NULL) {
            do {
                if (cur->flags.gatedLeft == 1 && (data_02060500 & 0x20) == 0) {
                    break;
                }
                if (next->groupId == cur->groupId || next->groupId == root->focused->groupId) {
                    break;
                }
                if (!next->flags.disabled && next->flags.focusable) {
                    SetFocusedWidget(root, next);
                    newDir = 0x20;
                    goto store_dir;
                }
                cur = next;
                next = next->left;
            } while (next != NULL);
        }
    } else if (dirs & (keys & 0x10)) {
        next = cur->right;
        if (next != NULL) {
            do {
                if (cur->flags.gatedRight == 1 && (data_02060500 & 0x10) == 0) {
                    break;
                }
                if (next->groupId == cur->groupId || next->groupId == root->focused->groupId) {
                    break;
                }
                if (!next->flags.disabled && next->flags.focusable) {
                    SetFocusedWidget(root, next);
                    newDir = 0x10;
                store_dir:
                    root->allowedDirs = newDir;
                    break;
                }
                cur = next;
                next = next->right;
            } while (next != NULL);
        }
    } else if ((keys & 1) && (confirm = cur->onConfirm) != NULL) {
        confirm(root->focused);
    }

    if (root->onInput == NULL) {
        return;
    }
    if ((keys & 0x2FFF) == 0) {
        return;
    }
    root->onInput(root->focused, keys);
}
