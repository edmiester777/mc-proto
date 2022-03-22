#pragma once

#define MC_PROTOCOL_VERSION 758

#define VLOG_DEBUG 1
#define VLOG_INFO 2
#define VLOG_WARN 3
#define VLOG_ERROR 4
#define VLOG_FATAL 5

#define asstr(v) #v

#include <iostream>
#include <sstream>
#include <memory>
#include <map>
#include <vector>
#include "safebytebuffer.h"
#include "mcstream.h"
#include "varint.h"
#include "uuid.h"

#if WIN32

#include <WinSock2.h>

#else

#include <arpa/inet.h>

#endif
