void CopyIntoByteBuffer(unsigned int *bufferState, char *sourceBytes, unsigned int requestedCount) {
    unsigned int byteOffset;
    unsigned int copyCount;
    if ((int)requestedCount > 0) {
        copyCount = bufferState[0];
        if (copyCount > requestedCount) {
            copyCount = requestedCount;
        }
        byteOffset = 0;
        if (byteOffset < copyCount) {
            do {
                *(unsigned char *)(bufferState[1] + byteOffset) = sourceBytes[byteOffset];
                byteOffset++;
            } while (byteOffset < copyCount);
        }
        bufferState[0] = bufferState[0] - copyCount;
        bufferState[1] = bufferState[1] + requestedCount;
    }
}
