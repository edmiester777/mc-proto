#include "compoundtag.h"
#include "compoundtag.h"
#include "compoundtag.h"
#include "compoundtag.h"
#include "compoundtag.h"
#include "compoundtag.h"
#include "compoundtag.h"
#include "compoundtag.h"

using namespace minecraft;

minecraft::NBTCompoundTag::NBTCompoundTag(istream& stream)
{

}

minecraft::NBTCompoundTag::NBTCompoundTag(const map<string, shared_ptr<NBTTagBase>> s)
{
}

NBTCompoundTag& minecraft::NBTCompoundTag::operator=(const NBTCompoundTag& other)
{
    throw exception("");
}

NBTCompoundTag& minecraft::NBTCompoundTag::operator=(const map<string, shared_ptr<NBTTagBase>>& children)
{
    throw exception("");
}

shared_ptr<NBTTagBase>& minecraft::NBTCompoundTag::operator[](const string& key)
{
    shared_ptr<NBTTagBase>t(nullptr);
    return t;
}

bool minecraft::NBTCompoundTag::contains(const string& key)
{
    return false;
}

NBTTagTypes minecraft::NBTCompoundTag::type() const
{
    return TAG_COMPOUND;
}

void minecraft::NBTCompoundTag::write_data(ostream& stream) const
{
}
