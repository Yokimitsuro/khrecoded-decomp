#ifndef NITRO_STD_STRING_INTERNAL_H
#define NITRO_STD_STRING_INTERNAL_H

char *STD_CopyString(char *destination, const char *source);
int STD_GetStringLength(const char *string);
char *STD_ConcatenateString(char *destination, const char *source);

#endif