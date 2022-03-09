#pragma once

#define NBT_MAP_TYPE std::map

#define VLOG_DEBUG 1
#define VLOG_INFO 2
#define VLOG_WARN 3
#define VLOG_ERROR 4
#define VLOG_FATAL 5

#include <istream>
#include <ostream>
#include <memory>
#include <map>
#include <variant>

#if WIN32

#include <WinSock2.h>

#else

#include <arpa/inet.h>

#endif