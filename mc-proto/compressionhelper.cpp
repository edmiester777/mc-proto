#include "compressionhelper.h"
#include <zlib.h>

using namespace minecraft;

safebytebuffer minecraft::CompressionHelper::compressGzip(safebytebuffer buffer)
{
    // do not use this function yet.
    throw E_NOTIMPL;
    return safebytebuffer();
}

safebytebuffer minecraft::CompressionHelper::decompressGzip(safebytebuffer buffer)
{
    return safebytebuffer();
}
