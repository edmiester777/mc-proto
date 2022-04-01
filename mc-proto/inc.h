#pragma once

#define between(v, l, h) (v >= l && v <= h)

#define MC_PROTOCOL_VERSION 758

#define MC_NUM_VERTICAL_CHUNKS 24
#define MC_CHUNK_WIDTH 16
#define MC_CHUNK_HEIGHT 16

#define VLOG_DEBUG 5
#define VLOG_INFO 4
#define VLOG_WARN 3
#define VLOG_ERROR 2
#define VLOG_FATAL 1

#define asstr(v) #v

#include <iostream>
#include <sstream>
#include <memory>
#include <map>
#include <vector>
#include <tuple>
#include "safebytebuffer.h"
#include "mcstream.h"
#include "varint.h"
#include "position.h"
#include "uuid.h"
#include "bitset.h"
#include "minecraft/entitytypes.h"

#if defined(WIN32) || defined(MSVC) || defined(_MSC_VER)

#include <WinSock2.h>

#else

#include <arpa/inet.h>

#endif

namespace minecraft
{
    using i8 = int8_t;
    using u8 = uint8_t;
    using i16 = int16_t;
    using u16 = uint16_t;
    using i32 = int32_t;
    using u32 = uint32_t;
    using i64 = int64_t;
    using u64 = uint64_t;

    using angle = u8;

    template <typename t>
    using sp = std::shared_ptr<t>;

    template <typename t>
    using unptr = std::unique_ptr<t>;
}
