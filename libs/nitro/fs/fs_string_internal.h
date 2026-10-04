#ifndef FS_STRING_INTERNAL_H
#define FS_STRING_INTERNAL_H

#include "libs/nitro/fs/fs_internal.h"

static inline BOOL STD_IsSjisLeadByte(int character)
{
    return (u32)((((u8)character) ^ 0x20) - 0xa1) < 0x3c;
}

static inline BOOL STD_IsSjisTrailByte(int character)
{
    return character != 0x7f && (u8)(character - 0x40) <= 0xbc;
}

static inline BOOL STD_IsSjisCharacter(const char *text)
{
    return STD_IsSjisLeadByte(text[0]) && STD_IsSjisTrailByte(text[1]);
}

static inline BOOL FSi_IsSlash(u32 character)
{
    return character == '/' || character == '\\';
}

static inline int FSi_IncrementSjisPosition(const char *text, int position)
{
    return position + 1 + STD_IsSjisLeadByte(text[position]);
}

#endif
