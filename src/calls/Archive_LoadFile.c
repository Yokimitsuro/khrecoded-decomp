extern void *FileLoader_LoadAlloc(void *file, int offset, int heap);

void *Archive_LoadFile(void *file, int heap)
{
    return FileLoader_LoadAlloc(file, 0, heap);
}