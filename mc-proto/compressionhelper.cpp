#include "compressionhelper.h"
#include <zlib.h>

using namespace minecraft;

safebytebuffer minecraft::CompressionHelper::compressGzip(safebytebuffer buffer)
{
    // do not use this function yet.
    throw E_NOTIMPL;

    const int bufLen = 1024;
    char writeBuf[bufLen];
    while (true)
    {
        
    }

    return safebytebuffer();
}

safebytebuffer minecraft::CompressionHelper::decompressGzip(safebytebuffer buffer)
{
    return safebytebuffer();
}
