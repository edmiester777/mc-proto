#pragma once

#define MC_PROTOCOL_VERSION 758

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
#include "safebytebuffer.h"
#include "mcstream.h"
#include "varint.h"
#include "position.h"
#include "uuid.h"
#include "minecraft/entitytypes.h"

#if WIN32

#include <WinSock2.h>

#else

#include <arpa/inet.h>

#endif

namespace minecraft
{
    typedef int8_t i8;
    typedef uint8_t u8;
    typedef int16_t i16;
    typedef uint16_t u16;
    typedef int32_t i32;
    typedef uint32_t u32;
    typedef int64_t i64;
    typedef uint64_t u64;

    typedef u8 angle;
}
