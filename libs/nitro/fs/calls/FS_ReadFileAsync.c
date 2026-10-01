typedef struct FSReadFileArgument {
    void *destination;
    int length;
} FSReadFileArgument;

typedef struct FSFile {
    unsigned char reserved[16];
    void *commandArgument;
    unsigned char commandState[28];
    FSReadFileArgument readArgument;
} FSFile;

typedef struct FSFileBounds {
    unsigned int imageTop;
    unsigned int imageBottom;
} FSFileBounds;

extern int FSi_GetFileLengthIfProc(FSFile *file, unsigned int *imageBottom);
extern int FSi_GetFilePositionIfProc(FSFile *file, unsigned int *imageTop);
extern int FSi_SendCommand(FSFile *file, int command, int synchronous);

int FS_ReadFileAsync(FSFile *file, void *destination, int length)
{
    FSFileBounds bounds;
    FSReadFileArgument *argument;

    if (FSi_GetFilePositionIfProc(file, &bounds.imageTop) == 0) {
        goto send;
    }
    if (FSi_GetFileLengthIfProc(file, &bounds.imageBottom) == 0) {
        goto send;
    }
    if (bounds.imageTop + length > bounds.imageBottom) {
        length = bounds.imageBottom - bounds.imageTop;
    }

send:
    argument = &file->readArgument;
    file->commandArgument = argument;
    argument->destination = destination;
    argument->length = length;
    FSi_SendCommand(file, 0, 0);
    return length;
}
