#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"
#include "login.h"

using namespace std;

minecraft::OutboundLoginPacket::OutboundLoginPacket(string username)
    : m_username(username)
{
}

void minecraft::OutboundLoginPacket::serialize_data(safebytebuffer& s) const
{
    s << m_username;
}

string minecraft::OutboundLoginPacket::username() const
{
    return m_username;
}
