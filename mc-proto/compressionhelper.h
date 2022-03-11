#pragma once

#include "inc.h"

namespace minecraft
{
    class CompressionHelper
    {
    public:
        static safebytebuffer compressGzip(safebytebuffer buffer);
        static safebytebuffer decompressGzip(safebytebuffer buffer);

    private:
        static void pushBytesToBuf(safebytebuffer& obuf, char* ibuf, int sizeibuf);
    };
}