#include "compressionhelper.h"
#include <zlib.h>

safebytebuffer minecraft::CompressionHelper::compressGzip(safebytebuffer buffer)
{
    // do not use this function yet.
    throw E_NOTIMPL;

    const int bufLen = 1024;
    char writeBuf[bufLen];
    while (true)
    {
        
    }
}

safebytebuffer minecraft::CompressionHelper::decompressGzip(safebytebuffer buffer)
{
    return safebytebuffer();
}

void minecraft::CompressionHelper::pushBytesToBuf(safebytebuffer& obuf, char* ibuf, int sizeibuf)
{
    // this strategy is in leau of the vector::insert method because we don't want to force
    // frequent re-allocations for expansion.

    // check if we need to resize buffer
    if (obuf.size() + sizeibuf > obuf.capacity())
    {
        // we will resize buffer to max(capacity * 2, sizeibuf * 2) to limit
        // future memory allocation/copy time.
        int newsize = max(obuf.capacity() * 2, sizeibuf * 2);
        obuf.resize(newsize);
    }

    // copying input buffer to next block location
    memcpy(&obuf[obuf.size()], ibuf, sizeibuf);
}
